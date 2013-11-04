#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE NAME_MAX 
ino_t get_inode(char*);
void printpathto(ino_t);
void inum_to_name(ino_t,char*,int);
int main(int argc, char** argv)
{
    printpathto(get_inode("."));
    putchar('\n');
    return 0;
}
ino_t get_inode(char* filename)
{
    struct stat info;
    if(stat(filename,&info)==-1)
    {
        fprintf(stderr,"Cannot stat");
        perror(filename);
        exit(1);
    }
    return info.st_ino;
}
void printpathto(ino_t this_node)
{
   ino_t my_inode;
   char its_name[BUFSIZE];
   if(get_inode("..")!=this_node)  //if this is not root
   {
      chdir("..");
      inum_to_name(this_node,its_name,BUFSIZE);
      my_inode=get_inode(".");
      printpathto(my_inode);    //recursive print
      printf("/%s",its_name);
   }
}
void inum_to_name(ino_t inode_to_find, char* namebuf, int bufsize)
{
    DIR* dir_ptr;
    struct dirent * direntp;
    dir_ptr=opendir(".");
    if(dir_ptr==NULL)
    {
        perror(".");
        exit(1);
    }
    while((direntp=readdir(dir_ptr))!=NULL)
    {
        if(direntp->d_ino == inode_to_find)
        {
            strncpy(namebuf, direntp->d_name, bufsize);
            namebuf[bufsize-1] = '\0';  //just in case
            closedir(dir_ptr);
            return ;
        }

    }
    fprintf(stderr, "error looking for inum %d\n",(int)inode_to_find);
    exit(1);

}
