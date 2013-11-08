#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define INPUTLEN 100
int main()
{
    void inthander(int);
    void quithander(int);
    char input[INPUTLEN];
    int nchars;

    signal(SIGINT, inthander);
    signal(SIGQUIT, quithander);

    do{
        printf("\nType a message:\n");
        nchars = read(0, input, INPUTLEN-1);
        if(nchars == -1)
            perror("read return an error");
        else {
            input[nchars] = '\0';
            printf("You typed: %s\n", input);
        }
    }while(strncmp(input,"quit",4)!=0);
    return 0;
}
void inthander(int s)
{
    printf("Received signal %d ....waiting\n", s);
    sleep(2);       /* 在debian7 上测试，此处sleep一直等待*/
    printf("Leaving inthander");
}
void quithander(int s)
{
    printf("Received signal %d ...Waiting\n", s);
    sleep(2);/* 在debian7 上测试，此处sleep一直等待*/
    printf("Leaving quithander");
}
