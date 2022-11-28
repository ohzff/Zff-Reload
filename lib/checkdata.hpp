#ifndef CHECKDATA
#define CHECKDATA

#include <cstring>
#include <stdio.h>
#include <sys/stat.h>
using namespace std;

bool checkdata ()
{
    struct stat buffer;   
    if (stat ("usr/world/1/main", &buffer) != 0)
    {
        printf ("Cannot read data! Please give 'usr/' folder me.\n");
        printf ("More info: https://github.com/ohzff/Zff-Reload/\n");
        return false;
    }
    return true;
}

#endif