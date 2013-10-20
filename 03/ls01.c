#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h>

void do_list(char*, bool);
bool start_dot(char*);
int main(int argc, char** argv)
{
    int a=0;
    bool flaga=false;
    if(argc==1)
        do_list(".",flaga);
    else 
        while((++a)<argc)
        {
            if(strcmp(argv[1],"-a")==0)
            {
                flaga=true;
                continue;
            }
            printf("%s",argv[a]);
            do_list(argv[a],flaga);
        }
    return 0;
}
void do_list(char* dir,bool flaga)
{
   DIR* dir_ptr;
   struct dirent* dirent;
   if((dir_ptr=opendir(dir))==NULL)
       fprintf(stderr,"ls1: cann't open %s",dir);
   while((dirent=readdir(dir_ptr))!=NULL)
   {
       if(!start_dot(dirent->d_name))
            printf("%s\n",dirent->d_name);
       else if(flaga)
            printf("%s\n",dirent->d_name);
   }
   closedir(dir_ptr);
}
bool start_dot(char* name)
{
    return name[0]=='.';
}
