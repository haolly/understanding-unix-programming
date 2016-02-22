#include <stdio.h>
#include <stdlib.h>
int main()
{
	char* cp = getenv("LANG");
	if(cp != NULL)
	{
		printf("%s\n", cp);
	}
	return 0;
}

