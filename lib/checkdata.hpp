#ifndef CHECKDATA
#define CHECKDATA

#include <cstring>
#include <cstdio>
#include <sys/stat.h>
using namespace std;

bool checkdata ()
{
    struct stat buffer;   
    if (stat ("usr/world/1/main", &buffer) != 0)
    {
        printf ("Cannot read data! Please give 'usr/' folder me.\n");
        return false;
    }
    return true;
}

#endif