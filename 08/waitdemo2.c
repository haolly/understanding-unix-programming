#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#define DELAY 	10

int main()
{
	int newPid;
	void child_code(int);
	void parent_code(int);
	printf("before: mypid is %d\n", getpid());
	if((newPid = fork()) == -1)
	{
		perror("fork");
	}
	else if(newPid == 0)
	{
		child_code(DELAY);
	}
	else 
	{
		parent_code(newPid);
	}
}

void child_code(int delay)
{
	printf("child %d here, will sleep for %d seconds\n", getpid(), delay);
	sleep(delay);
	printf("child done. abouut to exit\n");
	exit(17);
}

void parent_code(int childPid)
{
	int wait_rv;
	int child_status;
	int high_8, low_7, bit7;
	wait_rv = wait(&child_status);
	printf("done waiting for %d. Wait returned: %d\n", childPid, wait_rv);
	high_8 = child_status >>8;
	low_7 = child_status & 0x7f;
	bit7 = child_status & 0x80;
	printf("status:exit = %d, sig = %d, core = %d\n", high_8, low_7, bit7);

}
