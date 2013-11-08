#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#define INPUTLEN 100

int main()
{
    struct sigaction newhander;
    sigset_t blocked;
    void inthander(int);
    char x[INPUTLEN];

    newhander.sa_handler = inthander;
    newhander.sa_flags = SA_RESETHAND | SA_RESTART;

    sigemptyset(&blocked);
    sigaddset(&blocked, SIGQUIT);
    newhander.sa_mask = blocked;

    if(sigaction(SIGINT, &newhander, NULL)== -1)
        perror("sigaction error");
    else while(1)
    {
        fgets(x, INPUTLEN, stdin);
        printf("input %s\n",x);
    }

    return 0;
}
void inthander(int s)
{
    printf("Calling with signal %d\n", s);
    sleep(2);
    printf("Done handling signal %d\n", s);
}
