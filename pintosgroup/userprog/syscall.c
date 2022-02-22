#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "../devices/shutdown.h"
#include "../filesys/filesys.h"
#include "../filesys/file.h"
#include "threads/malloc.h"
#include "../lib/user/syscall.h"
#include "../threads/synch.h"
#include "../lib/kernel/console.h"
#include "../devices/input.h"


/* Prototypes*/
void syscall_init (void);
struct file *file_from_fd(int fd);
void halt(void);
void exit(int status);
bool create(const char *name, uint32_t initalsize);
int open(const char *file);
bool remove(const char *name);
int reading(int fd, void* buffer, unsigned size);
int write(int fd, const void* buffer, unsigned size);
void seek(int fd, unsigned pos);
unsigned tell(int fd);
static void syscall_handler (struct intr_frame *);



//Creating instance of our lock
struct lock lock;

//Creating instance of our file list
struct list *file_list;
    
//Creating instance of our file properties structure
struct file_props *file_props;

/**************************************************
* Function name : void syscall_init
*    returns    :
*    Args       : void
*
* Updated by    : Daniel Carter, Jonathan Palmer, Jonathan Salmon and William Butt
* Date created  : 03//01/21
* Description   : Initialises the file list and lock and passes control the syscall_handler
***************************************************/
void syscall_init (void)
{
  list_init (&file_list);
  lock_init(&lock);
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

/**************************************************
* Function name : struct file *file_from_fd
*    returns    : file
*    Args       : int fd
*
* Updated by    : Daniel Carter, Jonathan Palmer, Jonathan Salmon and William Butt
* Date created  : 03//01/21
* Description   : Loops through the file_list to match the fd given, returns file or exits
***************************************************/
struct file *file_from_fd(int fd)
{
  struct list_elem *e;
  // Loop to iterate through the list from beginning until end
  for (e = list_begin (&file_list); e != list_end (&file_list); 
        e = list_next (e))
    {
      //Populate file_props with current entry in list
      file_props= list_entry (e, struct file_props, elems);
      if(file_props->fd == fd)
      {
        return (file_props->file);
      }
    }
  //If no FD is matched return -1
  exit(-1);
}

/**************************************************
* Function name : void halt
*    returns    : the end of time
*    Args       : void
*
* Updated by    : Daniel Carter, Jonathan Palmer, Jonathan Salmon and William Butt
* Date created  : 28/12/20
* Description   : Calls to pintos shut down
***************************************************/
void halt (void)
{
  shutdown_power_off();
}

/**************************************************
* Function name : void exit
*    returns    :
*    Args       : int status
*
* Updated by    : Daniel Carter, Jonathan Palmer, Jonathan Salmon and William Butt
* Date created  : 03//01/21
* Description   : Exits the current thread, heavily influenced by Jon White
***************************************************/
void exit(int status)
{
  // Create a variable to hold the thread's information
  struct thread* cur=thread_current();
  // Give status to our thread struct so we can call it later
  cur->exit_code = status;
  // Exit the thread
  thread_exit();
}

/**************************************************
* Function name : bool create
*    returns    : boolean success - is file created?
*    Args       : const char *name, uint32_t initial_size
*
* Updated by    : Daniel Carter, Jonathan Palmer, Jonathan Salmon and William Butt
* Date created  : 2/1/21
* Description   : System call creating a new file inside the file system
***************************************************/
bool create (const char *name, uint32_t initial_size)
{
  return (bool)(filesys_create(name, initial_size));
}

/**************************************************
* Function name : bool remove
*    returns    : boolean success - is file removed?
*    Args       : const char *name
*
* Updated by    : Daniel Carter, Jonathan Palmer, Jonathan Salmon and William Butt
* Date created  : 2/1/21
* Description   : System call removing a file from inside the file system
***************************************************/
bool remove(const char *name)
{
  if(lock_try_acquire(&lock))
  {
    bool remove = filesys_remove(name);
    lock_release(&lock);
    return remove;

  }
  exit(-1);
}

/**************************************************
* Function name : int open
*    returns    : int file descriptor
*    Args       : const char *name
*
* Updated by    : Daniel Carter, Jonathan Palmer, Jonathan Salmon and William Butt
* Date created  : 2/1/21
* Description   : System call to open, add file to end of list
***************************************************/
int open(const char *file)
{
  //Creates an instance of a file based on whether it opened or not
  struct file *f = filesys_open(file);
  //Error handling for no file opened
  if(f == NULL)
  {
    return -1;
  }
 else
 { 
    // Struct for file properties
    if(lock_try_acquire(&lock))
    {
      //Gives page fault if you dont pre allocate memory
      file_props = malloc(sizeof *file_props);
      // Set file and fd
      file_props->file = f;
      int newfd = list_size(&file_list)+2; // not +1 because 1 is reserved for STDOUT_FILENO
      file_props->fd = newfd;
      // Add to the back of the list
      list_push_back(&file_list, &file_props->elems);
      lock_release(&lock);
      //Returns the FD
      return file_props->fd;
    }
    exit(-1);
 }  
}

/**************************************************
* Function name : int filesize
*    returns    : int file length
*    Args       : int fd (file descriptor)
*
* Updated by    : Daniel Carter, Jonathan Palmer, Jonathan Salmon and William Butt
* Date created  : 4/1/21
* Description   : System call to return file size by calling file_length in file.c
***************************************************/
int filesize(int fd)
{
  struct file *returnfile = file_from_fd(fd);
    if(lock_try_acquire(&lock))
    {
      //Error handling if no FD found
      if (returnfile == -1)
      {
        exit(-1);
      }
      else
      {
        // Calls file_length on the file returned from func given the fd
        int filesize = file_length(file_from_fd(fd));
        lock_release(&lock);
        return filesize;
      }
    }
    exit(-1);   
}
/**************************************************
* Function name : int read
*    returns    : int
*    Args       : int fd (file descriptor), const void* buffer (unallocated space), unsigned size (size of bytes going in buffer)
*
* Updated by    : Daniel Carter, Jonathan Palmer, Jonathan Salmon and William Butt
* Date created  : 6/1/21
* Description   : System call to read inside a file from current pos
***************************************************/
int reading(int fd, void *buffer, unsigned size)
{
  // file locking
  if(lock_try_acquire(&lock))
  {
    // error check for if fd is for writing instead of reading
    if (fd == STDOUT_FILENO)
    {
       lock_release(&lock);
       exit(-1);
    }
    // check if read is refereing to reading from console
    else if (fd == STDIN_FILENO)
    {
      int bytes;
      for(bytes; bytes<size; bytes+=1)
      {
        ((char *)buffer)[bytes] = input_getc();
      }
      lock_release(&lock);
      return bytes;
    }
    else
    {
      // read from the current position in the file and return how many bytes are actually read
      int bytes = file_read(file_from_fd(fd),buffer,size); 
      lock_release(&lock);
      return bytes;
    }
  }
  // if file lock fails
  exit(-1);
}


/**************************************************
* Function name : int write
*    returns    : int
*    Args       : int fd (file descriptor), const void* buffer (unallocated space), unsigned size (size of bytes going in buffer)
*
* Updated by    : Daniel Carter, Jonathan Palmer, Jonathan Salmon and William Butt
* Date created  : 6/1/21
* Description   : System call to write inside a file from current pos
***************************************************/
int write(int fd, const void* buffer, unsigned size)
{
  // get file lock
  if(lock_try_acquire(&lock))
  {
    // check if writing to console
    if (fd == STDOUT_FILENO)
    {
      putbuf(buffer, size);
      lock_release(&lock);
      return 0;
    }
    // error check for if reading from console
    else if (fd == STDIN_FILENO)
    {
       lock_release(&lock);
       exit(-1);
    }
    else
    {
      // write to the current position in the file and return how many bytes are actually written
      int bytes = file_write(file_from_fd(fd),buffer,size);
      // release the lock
      lock_release(&lock);
      return bytes;
    }
  }
  // error cherck for if the lock does not get acquired
  exit(-1);
}


/**************************************************
* Function name : void seek
*    returns    : void
*    Args       : int fd (file descriptor), unsigned pos (position)
*
* Updated by    : Daniel Carter, Jonathan Palmer, Jonathan Salmon and William Butt
* Date created  : 6/1/21
* Description   : System call to seek the next position to either read/write to.
***************************************************/
void seek(int fd, unsigned pos)
{
  // try to get a lock
  if(lock_try_acquire(&lock))
  {
    // change position in the file
    file_seek(file_from_fd(fd), pos);
    lock_release(&lock);
  }
  else
  {
    // if lock could not be acquired
    exit(-1);  
  }
}
/**************************************************
* Function name : int tell
*    returns    : int pos
*    Args       : int fd (file descriptor)
*
* Updated by    : Daniel Carter, Jonathan Palmer, Jonathan Salmon and William Butt
* Date created  : 5/1/21
* Description   : System call to return position of next byte to be read of written in file "fd"
***************************************************/
unsigned tell(int fd)
{
  // try and get a lock
  if(lock_try_acquire(&lock))
  {
    // get the current position in the file and put it into pos
    int pos = file_tell(file_from_fd(fd));
    lock_release(&lock);
    return pos;
  }
  // if lock can not be acquired
  exit(-1);
}

/**************************************************
* Function name : static void syscall_handler
*    returns    : void
*    Args: void *file_name_
*
* Updated by    : Daniel Carter, Jonathan Palmer, Jonathan Salmon and William Butt
* Date created  : 28/12/20
* Description   : Entering a switch statement to sort through the syscalls via the enum from
*                 esp.
*                 f->eax:set the return value for the calling process through the interrupt frame.
***************************************************/
static void syscall_handler (struct intr_frame *f UNUSED)
{
  bool success;
  // Dereference esp as an int to get relevant syscall
  int syscall_num = *((int*)f->esp);
  // printf("Syscall_handler() - %d\n", syscall_num);

  // Switch to go through all sys calls
  switch(syscall_num){
    case SYS_HALT: /* Halt the operating system. */
      printf("SYSCALL: Halt\n");
      halt();
    break;

    case SYS_EXIT:  /* Terminate this process. */
      printf("SYSCALL: Exit\n");
      // Declare a variable then increment by an int (4 bytes)
      // this allows us to get the 1st argument which is the return
      int status = *((int*) f->esp + 1);
      exit(status);
    break;

    case SYS_EXEC: /* Start another process. */
      printf("SYSCALL: Exec\n");
    break;

    case SYS_WAIT: /* Wait for a child process to die. */
      printf("SYSCALL: Wait \n");
    break;

    case SYS_CREATE: /* Create a file. */
      printf("SYSCALL: Create\n");
      // Declare the file variable then dereference esp into it
      char *file = *((int*)f->esp + 1); // +1 int to get the first argument
      // Get the arguments needed by the syscall
      uint32_t initial_size = *((int*) f->esp + 2); // +2 ints to get the second argument
      // Create the return variable and execute the create function
      success = create(file, initial_size);
      // See above description (line 55)
      f->eax = success;
    break;

    case SYS_REMOVE: /* Delete a file. */
      printf("SYSCALL: Remove\n");     
      // Run remove on the first argument on stack
      success = remove(*((int*)f->esp + 1));
      // See above description (line 55)
      f->eax = success;
    break;

    case SYS_OPEN : /* Open a file. */
      printf("SYSCALL: Open \n");
      // Run open on the first argument on stack
      int file_open = open(*((int*)f->esp + 1));
      //printf("File Descriptor: %d\n",file_open);
      // See above description (line 55)
      f->eax = file_open;
    break;

    case SYS_FILESIZE: /* Obtain a filef's size. */
      printf("SYSCALL: FileSize \n");
      //Run filesize on the first argument on stack
      int output = filesize(*((int*)f->esp + 1));
      //printf("file length = %d\n", output);
      // See above description (line 55)
      f->eax = output;
    break;

    case SYS_READ : /* Read from a file. */
      printf("SYSCALL: Read\n"); 
      // initialise the arguments: 1,2 and 3 from the stack
      int fd = (*((int*)f->esp + 1));
      void *buffer = (*((int*)f->esp + 2));
      unsigned size = (*((int*)f->esp + 3));
      // read, using the reading function and return how many bytes have been read
      int bytes_read = reading(fd, buffer, size);
      // return the amont of bytes read from the file or command line
      f->eax = bytes_read;
    break;

    case SYS_WRITE: /* Write to a file. */
      printf("SYSCALL: Write\n");
      // initialise the arguments: 1,2 and 3 from the stack
      fd = (*((int*)f->esp + 1));
      buffer = (*((int*)f->esp + 2));
      size = (*((int*)f->esp + 3));
      // call the write function and get how many bytes were written
      int bytes = write(fd, buffer, size);
      f->eax = bytes;
    break;

    case SYS_SEEK: /* Change position in a file. */
      // initialise the arguments: 1 and 2 from the stack
      printf("SYSCALL: Seek\n");
      fd = (*((int*)f->esp + 1));
      int pos = (*((int*)f->esp + 2));
      // run the seek command; does not return anything
      seek(fd, pos);
    break;

    case SYS_TELL : /* Report current position in a file. */
      printf("SYSCALL: Tell \n");
      // call the tell function and return the position
      pos = tell(*((int*)f->esp + 1));
      f->eax = pos;
    break;

    case SYS_CLOSE:  /* Close a file. */
      printf("SYSCALL:Close \n");
      // Run file_close on the first argument on stack
      file_close(file_from_fd(*((int*)f->esp + 1)));
    break;
  }
}
