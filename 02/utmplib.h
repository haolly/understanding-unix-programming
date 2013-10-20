#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <utmp.h>

#define NUECS 16
#define NULLUT ((struct utmp*)NULL)
#define UTSIZE (sizeof(struct utmp))

static char utmpbuf[NUECS*UTSIZE];
static int num_recs;
static int curr_recs;
static int fd_utmp=-1;

int utmp_open(char* filename)
{
    fd_utmp=open(filename,O_RDONLY);
    curr_recs=num_recs=0;
    return fd_utmp;
}

struct utmp* utmp_next()
{
    struct utmp* recp;
    if(fd_utmp==-1)
        return NULLUT;
    if((curr_recs==num_recs)&&(utmp_reload()==0))
    {
        return NULLUT;
    }
    recp = (struct utmp*)&utmpbuf[curr_recs*UTSIZE];
    curr_recs++;
    return recp;
}

int utmp_reload()
{
    int utmp_read=read(fd_utmp,utmpbuf,NUECS*UTSIZE);
    num_recs=utmp_read/UTSIZE;
    curr_recs=0;
    return num_recs;
}
void utmp_close()
{
    if(fd_utmp!=-1)
        close(fd_utmp);
}
