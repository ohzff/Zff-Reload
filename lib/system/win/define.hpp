#include <windows.h>

void syscls ()
{
    system ("cls");
}

const char CONPATH[20] = "CON";

#define OUTPUT_TIME 1
#define MOVEUP_TIME 100

void msleep (long x)
{
    Sleep (x);
}
