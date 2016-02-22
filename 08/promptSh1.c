#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXARGS		20
#define ARGLEN 		100

int execute(char* arglist[]);
char* makestring(char* );
int main()
{
	char* arglist[MAXARGS+1];
	int numargs;
	// 存储每次读入的参数
	char argbuf[ARGLEN];
	numargs = 0;
	while(numargs < MAXARGS)
	{
		printf("Arg[%d]?", numargs);
		if(fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n')
		{
			// 为什么不能直接使用 argbuf 而要拷贝一份，因为第二次赋值会覆盖第一次的信息
			arglist[numargs++] = makestring(argbuf);
		} 
		else 
		{
			if(numargs >0) 
			{
				arglist[numargs] = NULL;
				execute(arglist);
				numargs = 0;
			}
		}
	}
	return 0;
}

int execute(char* arglist[]) 
{
	execvp(arglist[0], arglist);
	perror("execvp failed");
	exit(1);
}

// 将 buf 中的内容拷贝一份
char* makestring(char* buf)
{
	char* cp;
	buf[strlen(buf) -1] = '\0';
	cp = (char*)malloc(strlen(buf) + 1);
	if(cp == NULL)
	{
		fprintf(stderr, "no memory\n");
		exit(1);
	}
	strcpy(cp, buf);
	return cp;
}
