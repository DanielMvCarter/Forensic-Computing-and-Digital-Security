#include <stdio.h> 
#include <string.h> 
  
int main() 
{ 
    char str[] = "filename arg1 arg2 arg3 arg4"; 
    char *save_ptr;
    int argc =0;
    // Returns first token 
    char* argv[50];
    char *token;
    
     argv[argc] = strtok_r(str, " ",&save_ptr); 
     argc++;
    // Keep printing args while one of the delimiters present in str[]. 
     while((token = strtok_r(NULL, " ", &save_ptr))!=NULL)
  {
    argv[(argc)++] = token;
    printf("Argument%d=",argc);
    printf("%s\n", argv[argc]);
  }

    // while (1) {
    //   argv[argc] =strtok_r(NULL, " ", &save_ptr);
    //   printf("Argument%d=",argc);
    //   printf("%s\n", argv[argc]);
    //   if (argv[argc]==NULL){
    //     break;
    //   }
    //     argc++;
    // }    
    return 0; 
}