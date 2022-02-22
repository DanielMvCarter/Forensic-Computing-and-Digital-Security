#include <stdio.h> 
#include <string.h> 
  
int main() 
{ 
    char str[] = "filename arg1 arg2 arg3 arg4"; 
    char *save_ptr;
    int argc =0;
    // Returns first token 
    char* argv[50];
    int i;
    int spaces =0;
    //Calculates the size of char array
    size_t size = sizeof(str) / sizeof(str[0]);
    //Loops through str while it is within size
    for(i=0;i<size;i++){
        if(str[i]==' '){
            spaces++;
        }
    }
    printf("Spaces=%d\n",spaces);
    argv[argc] = strtok_r(str, " ",&save_ptr); 
    // Keep printing args while one of the delimiters present in str[]. 
    while (argc<=spaces) {
        printf("Argument%d=",argc);
        printf("%s\n", argv[argc]);
        argc++;
        argv[argc] = strtok_r(NULL, " ", &save_ptr);
    }    
    return 0; 
}