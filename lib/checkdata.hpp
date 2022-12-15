#ifndef CHECKDATA
#define CHECKDATA

#include <cstring>
#include <stdio.h>
#include <sys/stat.h>
using namespace std;

bool checkdata (int &count)
{
    struct stat buffer;   
    if (stat ("usr/world/1/main", &buffer) != 0)
    {
        printf ("Cannot read data! Please give 'usr/' folder to me.\n");
        printf ("More info: https://github.com/ohzff/Zff-Reload/\n");
        return false;
    }
    freopen ("usr/world/count", "r", stdin);
    scanf ("%d", &count);
    freopen (CONPATH, "r", stdin);
    return true;
}

bool check_custom_data (char *name)
{
    char *p;
    strcpy (p, "usr/custom/world/");
    strcat (p, name);
    strcat (p, "/main");
    struct stat buffer;   
    if (stat (name, &buffer) != 0)
    {
        printf ("Cannot read data! Please check 'usr/custom/world' folder.\n");
        printf ("More info: https://github.com/ohzff/Zff-Reload/\n");
        return false;
    }
    return true;
}

#endif