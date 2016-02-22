#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int fd;
	int pid;
	char msg1[] = "Test 1 2 3\n";
	char msg2[] = "Hello world\n";
	if((fd = creat("testfile", 0644)) == -1) {
		return 0;
	}
	if(write(fd, msg1, strlen(msg1)) == -1) {
		return 0;
	}
	if((pid = fork()) == -1) {
		return 0;
	}
	if(write(fd, msg2, strlen(msg2)) == -1) {
		return 0;
	}
	close(fd);
	return 0;
}
