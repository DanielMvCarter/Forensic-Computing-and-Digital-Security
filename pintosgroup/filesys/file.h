#ifndef FILESYS_FILE_H
#define FILESYS_FILE_H
#include "lib/kernel/list.h"

#include "filesys/off_t.h"
#include "../lib/kernel/list.h"



/**************************************************
* Struct name   : file_props
*
* Created by    : Daniel Carter, Jonathan Palmer, Jonathan Salmon and William Butt
* Date created  : 28/12/20
* Description   : Struct to hold properties for file
***************************************************/
struct file_props
{
    struct file *file;          //The instance of the file
    int fd;                     //File descriptor
    struct list_elem elems;     //Part of list structure
};


struct inode;

/* Opening and closing files. */
struct file *file_open (struct inode *);
struct file *file_reopen (struct file *);
void file_close (struct file *);
struct inode *file_get_inode (struct file *);

/* Reading and writing. */
off_t file_read (struct file *, void *, off_t);
off_t file_read_at (struct file *, void *, off_t size, off_t start);
off_t file_write (struct file *, const void *, off_t);
off_t file_write_at (struct file *, const void *, off_t size, off_t start);

/* Preventing writes. */
void file_deny_write (struct file *);
void file_allow_write (struct file *);

/* File position. */
void file_seek (struct file *, off_t);
off_t file_tell (struct file *);
off_t file_length (struct file *);

#endif /* filesys/file.h */
