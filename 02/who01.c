#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>
#include <stdlib.h>
#include <time.h>
#include "utmplib.h"

#define SHOWHOST    /*include remote machine on output */
void show_info(struct utmp* utbufp);
void show_time(long);
int main(int argc, char** argv)
{
    /*
    struct utmp current_record;
    int utmpfd;
    int reclen = sizeof(struct utmp);
    if((utmpfd=open(UTMP_FILE,O_RDONLY))==-1)
    {
        perror(UTMP_FILE);
        exit(1);
    }
    while(read(utmpfd,&current_record,reclen)==reclen)
    {
        show_info(&current_record);
    }
    close(utmpfd);
    */
    struct utmp* utmpf;
    if((utmp_open(UTMP_FILE))==-1)
        perror(UTMP_FILE);

    while((utmpf=utmp_next())!=NULL)
        show_info(utmpf);
    utmp_close();

    return 0;
}
void show_info(struct utmp* utbufp)
{
    if(utbufp->ut_type!=USER_PROCESS)
        return ;
    printf("% -8.8s",utbufp->ut_user);
    printf(" ");
    printf("% -8.8s",utbufp->ut_line);
    printf(" ");
    //printf("%10ld",utbufp->ut_time);
    //printf(" ");
    show_time(utbufp->ut_time);
#ifdef SHOWHOST
    if(utbufp->ut_host[0]!='\0')
        printf("(%s)",utbufp->ut_host);
#endif
    printf("\n");
}
void show_time(long time)
{
    char* cp;
    cp = ctime(&time);
    printf("%s",cp);
    //it seems there is a '\n'

}
