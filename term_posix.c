#include <sys/ioctl.h>
#include <stdio.h>
#include "term.h"

int get_width()
{
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0)
    {
        return w.ws_col;
    }
    else
    {
        printf("Failed to get terminal width\n");
        return -1;
    }
}

int get_height()
{
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0)
    {
        return w.ws_row;
    }
    else
    {
        printf("Failed to get terminal height\n");
        return -1;
    }
}