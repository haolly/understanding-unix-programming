#include <stdio.h>
#include <termios.h>
#define QUESTION "Do you want another transaction"
/*how==0 > save current mode how==1 >restore mode */
void tty_mode(int how)
{
    static struct termios original_mode;
    if(how == 0)
    {
        tcgetattr(0,&original_mode);
        //0 is the standard input
    }
    else 
        tcsetattr(0,TCSANOW, &original_mode);
}
void set_rc_noecho_mode();
int get_response(char*);
int main()
{
    int response;
    tty_mode(0);
    set_rc_noecho_mode();
    response = get_response(QUESTION);
    tty_mode(1);
    return response;
}
void set_rc_noecho_mode()
{
    struct termios ttystate;
    tcgetattr(0,&ttystate);
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_lflag &= ~ECHO;
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(0,TCSANOW,&ttystate);
}
int get_response(char* question)
{
    printf("%s (y/n)?",question);
    while(1)
    {
        switch(getchar())
        {
            case 'Y':
            case 'y':
                return 0;
            case 'N':
            case 'n':
            case EOF:
                return 1;
        }
    }
}
