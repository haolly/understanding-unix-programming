#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


#define oops(m, x) {perror(m); exit(x);}
void fatal(const char* message);
void be_bc(int in[2], int out[2]);
void be_dc(int in[2], int out[2]);

int main(int argc, char *argv[])
{
	// pipe[0] for read, pipe[1] for write
	int pid, todc[2], fromdc[2];
	if(pipe(todc) == -1 || pipe(fromdc) == -1)
	{
		oops("pipe failed", 1);
	}
	if((pid = fork()) == -1)
	{
		oops("cannot fork", 2);
	}

	if(pid == 0)
	{
		//child
		be_dc(todc, fromdc);
	}
	else {
		be_bc(todc, fromdc);
		wait(NULL);
	}
	return 0;
}
void be_dc(int in[2], int out[2])
{
	// setup stdin from pipein
	if(dup2(in[0], 0) == -1)
	{
		oops("dc: cannot redirect stdin", 3);
	}
	close(in[0]);
	close(in[1]);

	// setup stdout to pipout
	if(dup2(out[1], 1) == -1)
	{
		oops("dc: cannot redirect stdout", 4);
	}
	close(out[0]);
	close(out[1]);

	execlp("dc", "dc", "-", NULL);
	oops("Cannot run dc", 5);
}

void be_bc(int todc[2], int fromdc[2])
{
	int num1, num2;
	char operation[BUFSIZ], message[BUFSIZ];
	FILE *fpout, *fpin;

	close(todc[0]);
	close(fromdc[1]);

	// pipe[1] for write, could read from pipe[0]
	fpout = fdopen(todc[1],"w");
	// pipe[0] for read
	fpin = fdopen(fromdc[0], "r");

	if(fpout == NULL || fpin == NULL)
	{
		fatal("Error converting pipes to stream");
	}
	while(printf("tinybc:"), fgets(message, BUFSIZ, stdin) != NULL)
	{
		if(sscanf(message, "%d %[- + * / ^] %d", &num1, operation, &num2) != 3)
		{
			printf("syntax error\n");
			continue;
		}

		// send input to dc
		if(fprintf(fpout, "%d\n %d\n %c\n p \n", num1, num2, *operation) == EOF)
		{
			fatal("Error writing");
		}
		//make sure to write
		fflush(fpout);
		// get result from dc
		if(fgets(message, BUFSIZ, fpin) == NULL)
			break;
		printf("%d %c %d = %s", num1, *operation, num2, message);
	}

	fclose(fpout);
	fclose(fpin);
}

void fatal(const char* message)
{
	fprintf(stderr, "Error: %s\n", message);
	exit(1);
}
