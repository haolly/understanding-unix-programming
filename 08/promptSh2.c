#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define MAXARGS		20
#define ARGLEN 		100

char* makeString(char* buf);
void execute(char**);
int main(int argc, char *argv[])
{
	char* arglist[MAXARGS + 1];
	int numArgs;
	char argBuf[ARGLEN];
	numArgs = 0;
	while(numArgs <MAXARGS) 
	{
		printf("arg[%d]?\n", numArgs);
		if(fgets(argBuf, ARGLEN, stdin) && *argBuf != '\n')
		{
			arglist[numArgs++] = makeString(argBuf);
		}
		else
		{
			if(numArgs >0)
			{
				arglist[numArgs] = NULL;
				execute(arglist);
				numArgs = 0;
			}
		}
	}
	return 0;
}

void execute(char* arglist[])
{
	int pid, exitStatus;
	pid = fork();
	switch(pid)
	{
		case 0:
			execvp(arglist[0], arglist);
			// the two line below will never be executed !!!
			perror("execvp failed");
			exit(1);
			break;
		case -1:
			perror("fork");
			break;
		default:
			while(wait(&exitStatus) != pid)
			{

			}
			printf("child exited with status %d, %d\n",exitStatus>>8, exitStatus & 0377 );
	}
}

// fgets will read the newline character '\n' into destination
char* makeString(char* buf)
{
	char* ret;
	buf[strlen(buf) - 1] = '\0';	// trim newline, make the buf Null-terminated
	int len = strlen(buf);
	ret = (char*)malloc(len +1);
	strcpy(ret, buf);
	return ret;
}
