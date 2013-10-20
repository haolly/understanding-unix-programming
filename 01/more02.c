#include <stdio.h>
#include <stdlib.h>
#define LINELEN 512
#define PAGELEN 24
void do_more(FILE* f);
int see_more(FILE* cmd);
int main(int argc, char** argv)
{
    FILE* fp;
    if(argc==1)
        do_more(stdin);
    else 
        while(--argc)
        {
            if((fp=fopen(*(++argv),"r"))!=NULL)
            {
                do_more(fp);
                fclose(fp);
            }
            else
                exit(1);
        }
    return 0;
}
void do_more(FILE* fp)
{
    char line[LINELEN];
    int num_of_lines=0;
    int reply;
    FILE* tty_file;
    if((tty_file=fopen("/dev/tty","r"))==NULL)
        exit(1);

    while(fgets(line,LINELEN,fp))
    {
        if(num_of_lines==PAGELEN)
        {
            reply=see_more(tty_file);
            if(reply==0)
                break;
            num_of_lines-=reply;    
        }
        if(fputs(line,stdout)==EOF)
            exit(1);
        num_of_lines++;

    }
}
int see_more(FILE* cmd)
{
    int c;
    printf("more?");
    while((c=fgetc(cmd))!=EOF)
    {
        if(c=='q')
            return 0;
        if(c==' ')
            return PAGELEN;
        if(c=='\n')
            return 1;
    }
    return 0;
}
