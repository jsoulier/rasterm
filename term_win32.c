#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include "term.h"

int get_width()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    else
    {
        printf("Failed to get console width\n");
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
        printf("Failed to get console height\n");
        return -1;
    }
}