#include <stdio.h>
#include <unistd.h>
int main()
{
	int fork_rv;
	printf("Before, my pid is %d \n", getpid());
	fork_rv = fork();
	if(fork_rv == -1)
	{
		perror("fork");
	}
	else if(fork_rv == 0) 
	{
		printf("I am the child, my pid is %d\n", getpid());
	}
	else 
	{
		printf("I am the parent, my child is %d\n", fork_rv);
	}
	return 0;
}
