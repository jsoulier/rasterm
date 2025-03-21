#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "path.h"

bool set_filename(
    const char* root,
    const char *filename,
    char* path)
{
    strcpy(path, root);
    char* seperator;
    char* forward = strrchr(path, '/');
    char* backward = strrchr(path, '\\');
    if (forward < backward)
    {
        seperator = backward;
    }
    else
    {
        seperator = forward;
    }
    if (!seperator)
    {
        printf("Invalid path: %s\n", path);
        return false;
    }
    *(seperator + 1) = '\0';
    strcat(seperator, filename);
    return true;
}