#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	struct sockaddr_in server_add;
	struct hostent* hp;
	int socket_id;
	char message[BUFSIZ];
	int messlen;
	socket_id = socket(AF_INET, SOCK_STREAM, 0);
	memset(&server_add, 0, sizeof(server_add));

	hp = gethostbyname(argv[1]);
	if(hp == NULL)
	{
		return 1;
	}
	memcpy(&server_add.sin_addr, hp->h_addr, hp->h_length);
	server_add.sin_port = htons(atoi(argv[2]));
	server_add.sin_family = AF_INET;
	if(connect(socket_id, (struct sockaddr*)&server_add, sizeof(server_add)) != 0)
	{
		return 2;
	}
	messlen = read(socket_id, message, BUFSIZ);
	if(messlen == -1)
	{
		return 3;
	}
	write(1, message, messlen);
	close(socket_id);
	return 0;
}
