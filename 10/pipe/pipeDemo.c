#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int len, i, apipe[2];
	char buf[256];

	if(pipe(apipe) == -1)
	{
		perror("could not make pipe");
		exit(1);
	}
	printf("Got a pipe! It is file descriptors: { %d %d }\n", apipe[0], apipe[1]);
	while(fgets(buf, 256, stdin))
	{
		len = strlen(buf);
		if(write(apipe[1], buf, len) != len)
		{
			perror("writing ti pipe");
			break;
		}
		for(i=0; i<len; i++)
		{
			buf[i] = 'X';
		}
		len = read(apipe[0], buf, 256);
		if(len == -1)
		{
			perror("reading from pipe");
			break;
		}
		if(write(1, buf, len) != len)
		{
			perror("writeing to stdout");
			break;
		}
	}
	return 0;
}
