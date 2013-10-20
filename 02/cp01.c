#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE 4096
#define COPMODE 0644

void oops(char*, char*);
int main(int argc, char** argv)
{
    int in_fd, out_fd, n_chars;
    char buf[BUFSIZE];

    if(argc!=3)
    {
        fprintf(stderr,"usage:%s source destination\n",*argv);
        exit(1);
    }

    if((in_fd=open(argv[1],O_RDONLY))==-1)
        oops("Cann't open", argv[1]);
    if((out_fd=creat(argv[2],COPMODE))==-1)
        oops("Cann't creat", argv[2]);

    while((n_chars=read(in_fd,buf,BUFSIZE))>0)
        if(write(out_fd,buf,n_chars)!=n_chars)
            oops("Write error to", argv[2]);
    if(n_chars==-1)
        oops("Read error from",argv[1]);

    if(close(in_fd)==-1||close(out_fd)==-1)
        oops("Close file error","");

    return 0;
}
void oops(char* err,char* err2)
{
    fprintf(stderr,"Error: %s",err);
    perror(err2);
    exit(1);
}
