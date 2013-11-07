#include <stdio.h>
#include <signal.h>
#include <unistd.h>
int main()
{
    void f(int);
    int i;
    signal(SIGINT, f);
    for(i=0;i<5;i++)
    {
        printf("hello world\n");
        sleep(1);
    } 
    return 0;
}
void f(int signal)
{
    printf("oohps\n");
}
