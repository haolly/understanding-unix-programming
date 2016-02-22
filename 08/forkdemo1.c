#include <stdio.h>
#include <unistd.h>
int main()
{
	int ret_from_fork=-1, myPid;
	myPid = getpid();
	printf("Before: myPid is %d\n", myPid);
	ret_from_fork = fork();
	sleep(1);
	printf("After: myPid is %d, fork() said %d\n",getpid(), ret_from_fork);
	return 0;
}
