#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <features.h>
struct flaginfo
{
    int fl_value;
    char* fl_name;
};
struct flaginfo local_flags[]=
{
    {ISIG, "Enble signal"},   
    {ICANON, "Cannonical input (erase and kill)"},
    {ECHO, "Enable echo"},
    {ECHOE, "Echo ERASE as BS-SPACE-BS"},
    {ECHOK, "Echo KILL by starting new line"},
    {0, NULL}
};
struct flaginfo input_flags[]=
{
    {IGNBRK, "Ignore break condition"},
    {BRKINT, "Signal interrupt on break"},
    {IGNPAR, "Ignore chars with parity erros"},
    {PARMRK, "Mark parity errors"},
    {INPCK, "Enable input parity check"},
    {ISTRIP, "Strip character"},
    {INLCR, "Map NL to CR on input"},
    {IGNCR, "Ignore CR"},
    {ICRNL, "Map CR to NL on input"},
    {IXON, "Enable start/stop output control"},
    {IXOFF, "Enable start/stop input control"},
    {0, NULL}
    
};
void showbaud(int thespeed);
void show_flagset(int thevalue, struct flaginfo thebitnames[]);
void show_some_flag(struct termios* ttyp);
int main()
{
    struct termios ttyinfo;
    if(tcgetattr(0, &ttyinfo)==-1)
    {
        perror("cann't not get params about stdin");
        exit(1);
    }
    showbaud((int)cfgetospeed(&ttyinfo));
    printf("The erase character is ascii %d, Ctrl-%c\n",
            ttyinfo.c_cc[VERASE], ttyinfo.c_cc[VERASE]-1+'A');
    printf("The line kill character is ascii %d, Ctrl-%c\n",
            ttyinfo.c_cc[VKILL], ttyinfo.c_cc[VKILL]-1+'A');
    show_some_flag(&ttyinfo);
    return 0;
}
void showbaud(int thespeed)
{
    printf("The baud rate is");
    switch(thespeed)
    {
        case B300:
            printf("300\n");break;
        case B600:
            printf("600\n");break;
        case B1200:
            printf("1200\n");break;
        case B1800:
            printf("1800\n");break;
        case B2400:
            printf("2400\n");break;
        case B4800:
            printf("4800\n");break;
        case B9600:
            printf("9600\n");break;
        default:
            printf("Fast\n");break;
    }
}



void show_some_flag(struct termios* ttyp)
{
    show_flagset(ttyp->c_iflag, input_flags);
    show_flagset(ttyp->c_lflag, local_flags);
}
void show_flagset(int thevalue, struct flaginfo thebitnames[])
{
    int i;
    for(i=0;thebitnames[i].fl_value;i++)
    {
        printf("%s is", thebitnames[i].fl_name);
        if(thevalue & thebitnames[i].fl_value)
            printf("ON\n");
        else 
            printf("OFF\n");
    }
}
