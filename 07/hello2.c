#include <stdio.h>
#include <curses.h>
int main()
{
    int i;
    initscr();
    clear();
    for(i=0;i<LINES;i++)
    {
        move(i,i+i);
        if(i%2==1)
        {
            standout();     /*是屏幕反色*/
        }
        addstr("Hello world");
        if(i%2==1)
            standend();     /*恢复正常*/
    }
    refresh();
    getch();
    endwin();
}
