#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "smsh.h"

#define DFL_PROMPT ">"

void setup();
int main(int argc, char *argv[])
{
	char *cmdline, *prompt, **arglist;
	int result;

	prompt = (char*)DFL_PROMPT; 
	setup();

	while((cmdline = next_cmd(prompt, stdin)) != NULL) {
		if((arglist = splitline(cmdline)) != NULL) {
			result = execute(arglist);
			freelist(arglist);
		}
		free(cmdline);
	}
	return 0;
}

void setup()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n)
{
	fprintf(stderr, "Error: %s, %s\n", s1, s2);
	exit(n);
}

