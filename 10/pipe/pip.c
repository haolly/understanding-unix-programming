#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define oops(m, x) 	{perror(m); exit(x);}

int main(int argc, char *argv[])
{
	fprintf(stderr, "%s %s %s", argv[0], argv[1], argv[2]);
	int pipefd[2], newfd, pid;
	if(argc != 3)
	{
		fprintf(stderr, "usage: pip cmd1 cmd2");
		exit(1);
	}
	if(pipe(pipefd) == -1)
	{
		oops("Cann't get a pip", 1);
	}
	if((pid = fork()) == -1)
	{
		oops("Cann't fork", 2);
	}
	if(pid == 0)
	{
		//close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		execlp(argv[1],argv[1]);
		oops(argv[1], 4);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		execlp(argv[2], argv[2]);
		oops(argv[1], 5);
	}
	return 0;
}
