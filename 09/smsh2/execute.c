#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int execute(char *argv[])
{
	int pid;
	int child_info = -1;
	if(argv[0] == NULL) {
		return 0;
	}else if((pid = fork()) == -1) {
		perror("fork");
	}else if(pid == 0) {
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execvp(argv[0], argv);
		perror("cannot execute command");
		exit(1);
	}else{
		if(wait(&child_info) == -1) {
			perror("Wait");
		}
	}
	return child_info;
}
