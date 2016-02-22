#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#define DELY 	2
int main()
{
	int newPid;
	void child_code(int);
	void parent_code(int);
	printf("before, mypid is %d\n", getpid());
	if((newPid = fork()) == -1)
	{
		perror("fork");
	}
	else if(newPid == 0) 
	{
		child_code(DELY);
	}
	else
	{
		parent_code(newPid);
	}
}

void child_code(int dely)
{
	printf("child %d here. will sleep for %d seconds\n", getpid(), dely);
	sleep(dely);
	printf("child done, about to exit\n");
	exit(17);
}

void parent_code(int childPid)
{
	int wait_rv;
	wait_rv = wait(NULL);
	printf("done waiting for %d. Wait return: %d\n", childPid, wait_rv);
}
