#include <stdio.h>
#include "term.h"
#include "win32.h"

int get_width()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    else
    {
        printf("Failed to get terminal width\n");
        return -1;
    }
}

int get_height()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    else
    {
        printf("Failed to get terminal height\n");
        return -1;
    }
}