#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int i;
	for (i = 0; i < 10; ++i) {
		printf("my pid = %d, n= %d\n", getpid(), i);
		sleep(1);
	/*	if(fork() != 0) {
			exit(0);
		} */
	}
	return 0;
}
