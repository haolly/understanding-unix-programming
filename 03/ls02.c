#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include "utility.h"
void do_list(char*);
void dostat(char*);
void show_file_info(char*, struct stat*);
void mod_to_letters(int , char*);
char* uid_to_name(uid_t);
char* gid_to_name(gid_t);
int main(int argc, char** argv)
{
    if(argc==1)
        do_list(".");
    else 
        while(--argc)
        {
            printf("%s:\n",*++argv);
            do_list(*argv);
        }
    return 0;

}
void do_list(char* dirname)
{
    DIR* dir_ptr;
    struct dirent* dirent;

    if((dir_ptr=opendir(dirname))==NULL)
        fprintf(stderr,"ls can't open %s\n",dirname);
    else 
    {
        while((dirent=readdir(dir_ptr))!=NULL)
        {
            dostat(dirent->d_name);
        }
        closedir(dir_ptr);
    }
}
void dostat(char* file)
{
    struct stat info;
    if((stat(file,&info)==-1))
        perror(file);
    else
    {
        show_file_info(file,&info);
    }
}
void show_file_info(char* filename, struct stat * info)
{
    char mode[10];
    mod_to_letters(info->st_mode,mode);
    printf("%s",mode);
    printf("%4d",(int)info->st_nlink);
    printf("%8s",uid_to_name(info->st_uid));
    printf("%8s",gid_to_name(info->st_gid));
    printf("%10ld",(long)info->st_size);
    printf("%.12s",4+ctime(&info->st_mtime));
    printf("%s\n",filename);
}
void mod_to_letters(int mode, char* str)
{
    strcpy(str,"----------");
    if(S_ISDIR(mode))
        str[0]='d';
    if(S_ISCHR(mode))
        str[0]='c';
    if(S_ISBLK(mode))
        str[0]='b';

    if(mode& S_IRUSR)
        str[1]='r';
    if(mode& S_IWUSR)
        str[2]='w';
    if(mode & S_IXUSR)
        str[3]='x';

    if(mode & S_IRGRP)
        str[4]='r';
    if(mode & S_IWGRP)
        str[5]='w';
    if(mode & S_IXGRP)
        str[6]='x';

    if(mode & S_IROTH)
        str[7]='r';
    if(mode & S_IWOTH)
        str[8]='w';
    if(mode & S_IXOTH)
        str[9]='x';

}
