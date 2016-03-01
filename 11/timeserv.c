#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <strings.h>

const int port = 13000;
const int hostLen = 256;
#define oops(msg) 	{perror(msg); exit(1);}
int main(int argc, char *argv[])
{
	struct sockaddr_in saddr;
	struct hostent* hp;
	char hostName[hostLen];
	int sock_id, sock_fd;
	FILE* sock_fp;
	time_t theTime;

	sock_id = socket(PF_INET, SOCK_STREAM, 0);
	if(sock_id == -1)
	{
		oops("socket");
	}
	//bzero((void*)&saddr, sizeof(saddr));
	memset(&saddr, 0, sizeof(saddr));
	gethostname(hostName, hostLen);
	hp = gethostbyname(hostName);

	//bcopy((void*)hp->h_addr, (void*)&saddr.sin_addr, hp->h_length);
	memcpy(&saddr.sin_addr, hp->h_addr, hp->h_length);
	saddr.sin_port = htons(port);
	saddr.sin_family = AF_INET;

	if(bind(sock_id, (struct sockaddr*)&saddr, sizeof(saddr)) != 0)
	{
		oops("bind");
	}
	
	if(listen(sock_id, 1) != 0)
	{
		oops("listen");
	}

	while(1)
	{
		sock_fd = accept(sock_id, NULL, NULL);
		printf("Get a call\n");
		if(sock_fd == -1)
		{
			oops("accept");
		}
		sock_fp = fdopen(sock_fd, "w");
		if(sock_fp == NULL)
		{
			oops("fdopen");
		}
		theTime = time(NULL);
		fprintf(sock_fp, "the time is ..");
		fprintf(sock_fp, "%s", ctime(&theTime));
		fclose(sock_fp);
	}
	return 0;
}
