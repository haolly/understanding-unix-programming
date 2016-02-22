#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define CHILD_MESS 	"I want a cookie\n"
#define PAR_MESS 	"testing.. \n"
#define oops(m, x) 	{perror(m); exit(x);}

int main(int argc, char *argv[])
{
	int pipefd[2];
	int len;
	char buf[256];
	int read_len;
	if(pipe(pipefd) == -1)
	{
		oops("cann't get a pip", 1);
	}
	switch (fork()) {
		case -1:
			oops("cann't fork", 2);
			break;
		case 0:	// child thread
			len = strlen(CHILD_MESS);
			while(1)
			{
				if(write(pipefd[1], CHILD_MESS, len) != len)
				{
					oops("write", 3);
				}
				sleep(5);
			}
		default:
			len = strlen(PAR_MESS);
			while(1)
			{
				if(write(pipefd[1], PAR_MESS, len) != len)
				{
					oops("write", 4);
				}
				sleep(1);
				read_len = read(pipefd[0], buf, 256);
				if(read_len <0)
				{
					break;
				}
				write(1, buf, read_len);
			}
	}
	return 0;
}
