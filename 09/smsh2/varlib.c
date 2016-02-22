#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXVARS 200

struct var
{
	char* str;
	int global;
};

static struct var tab[MAXVARS];

static char* new_string(const char*,const char*);

struct var* find_item(const char* name, int first_blank)
{
	int i = 0;
	int len = strlen(name);
	char* s;
	for (i = 0; i < MAXVARS && tab[i].str != NULL; ++i) {
		s = tab[i].str;
		if(strncmp(s, name, len) == 0 && s[len] == '=')
		{
			// if find key name and the value
			return &tab[i];
		}
	}
	if(i<MAXVARS && first_blank)
	{
		return &tab[i];
	}
	return NULL;
}

int VLstore(const char* name, const char* val)
{
	struct var* item;
	char* s;
	int rv = 1;
	if((item = find_item(name, 1)) != NULL && (s = new_string(name, val)) != NULL)
	{
		if(item->str)
		{
			free(item->str);
		}
		item->str = s;
		rv = 0;
	}
	return rv;
}

char* new_string(const char* name, const char* val)
{
	char* retval = (char*) malloc(strlen(name) + strlen(val) + 2);
	if(retval != NULL)
	{
		sprintf(retval, "%s=%s", name, val);
	}
	return retval;
}

const char* VLlookup(char* name)
{
	struct var* item;
	if((item = find_item(name, 0)) != NULL)
	{
		// return the value
		return item->str + 1 + strlen(name);
	}
	return "";
}

int VLexport(char* name)
{
	struct var* item;
	int rv = 1;
	if((item = find_item(name, 0)) != NULL)
	{
		item->global = 1;
		rv = 0;
	}
	else if(VLstore(name, "") == 1)
	{
		rv = VLexport(name);
	}
	return rv;
}

void VLlist()
{
	int i;
	for(i=0; i<MAXVARS && tab[i].str != NULL; i++)
	{
		if(tab[i].global)
			printf("* %s\n", tab[i].str);
		else
			printf("%s\n", tab[i].str);
	}
}

int VLenviron2table(char* env[])
{
	int i;
	char* newstring;
	for(i=0; env[i] != NULL; i++)
	{
		if(i == MAXVARS)
			return 1;
		newstring = (char*)malloc(strlen(env[i]) + 1);
		if(newstring == NULL)
			return 1;
		strcpy(newstring, env[i]);
		tab[i].str = newstring;
		tab[i].global = 1;
	}
	while(i<MAXVARS)
	{
		tab[i].str = NULL;
		tab[i].global = 0;
		i++;
	}
	return 0;
}

const char** VLtable2env()
{
	int tab_size = 0;
	for(int i=0; i<MAXVARS && tab[i].str != NULL; i++)
	{
		tab_size++;
	}
	const char** env = (const char**)malloc((tab_size + 1) * sizeof(char*));
	env[tab_size] = "\0";
	for (int i = 0; i < tab_size; ++i) {
		char *str = (char*)malloc(strlen(tab[i].str) + 1);
		strncmp(str, tab[i].str, strlen(tab[i].str));
		env[i] = str;
	}
	return env;
}
