#ifndef CHECKDATA
#define CHECKDATA

#include <cstring>
#include <stdio.h>
#include <sys/stat.h>
using namespace std;

bool checkdata (int &count)
{
    struct stat buffer;
    char testpath[200];
    printf ("Reading usr/ from \"%s\"...\n", DATAPATH);
    if (stat (getdatapath ("usr/world/1/main"), &buffer) != 0)
    {
        printf ("Cannot read data! Please give 'usr/' folder to me.\n");
        printf ("More info: https://github.com/ohzff/Zff-Reload/\n");
        printf ("    INFO: datapath = \"%s\".\n", DATAPATH);
        return false;
    }
    freopen (getdatapath ("usr/world/count"), "r", stdin);
    scanf ("%d", &count);
    freopen (CONPATH, "r", stdin);
    return true;
}

bool check_custom_data (char *name)
{
    char p[200];
    strcpy (p, getdatapath ("usr/custom/world/"));
    strcat (p, name);
    strcat (p, "/main");
    struct stat buffer;   
    if (stat (p, &buffer) != 0)
    {
        printf ("Cannot read data! Please check 'usr/custom/world' folder.\n");
        printf ("More info: https://github.com/ohzff/Zff-Reload/\n");
        return false;
    }
    return true;
}

#endif