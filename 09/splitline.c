#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// read a line until '\n'
// the reason do not use fgets is tha we could not know the length of the line
char* next_cmd(char *prompt, FILE *fp)
{
	char *buf;
	int bufspace = 0;
	int pos = 0;
	int c;
	printf("%s",prompt);
	while((c = getc(fp)) != EOF) {
		if(pos + 1 >= bufspace) {
			if(bufspace == 0) {
				buf = malloc(BUFSIZE);
			}else {
				buf = realloc(buf, bufspace + BUFSIZE);
			}
			bufspace += BUFSIZE;
		}	
		if(c == '\n') {
			break;
		}
		buf[pos++] = c;
	}
	if(c == EOF && pos == 0) {
		return NULL;
	}

	buf[pos] = '\0';
	return buf;
}

#define is_delim(x) ((x) == ' ' || (x) == '\t')

char** splitlien(char *line)
{
	char* newstr();
	char** args;
	int spots = 0;
	int bufspace = 0;
	int argnum = 0;
	char* cp = line;
	char* start;
	int len;
	if(line == NULL) {
		return NULL;
	}
	args = (char**)malloc(BUFSIZE);
	bufspace = BUFSIZE;
	spots = BUFSIZE/sizeof(char*);
	
	while(*cp != '\0') {
		//only skip leading spaces
		while(is_delim(*cp)) {
			cp++;
		}
		if(*cp == '\0'){
			break;
		}
		if(argnum + 1 >= spots) {
			args = realloc(args, bufspace + BUFSIZE);
			bufspace += BUFSIZE;
			spots += (BUFSIZE/sizeof(char*));
		}
		start = cp;
		len = 1;
		while(*++cp != '\0' && !(is_delim(*cp))) {
			len++;
		}
		args[argnum] = newstr(start, len);
	}
	args[argnum] = NULL;
	return args;
}

char* newstr(char* s, int len)
{
	char* rv = malloc(len + 1);
	rv[len] = '\0';
	strncpy(rv,s, len);
	return rv;
}

void freelist(char** list)
{
	char** cp = list;
	while(*cp) {
		free(*cp++);
	}
	free(list);
}

void* emalloc(size_t n)
{
	void* rv;
	if((rv = malloc(n)) == NULL) {
		fatal("out of memory","", 1);
	}
	return rv;
}

