#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

ino_t get_inode(char*);
void printpathto(ino_t);
void inum_to_name(ino_t,char*,int);
int main(int argc, char** argv)
{
    printpathto(get_inode("."));
    putchar('\n');
    return 0;
}

