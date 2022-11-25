#ifdef SYSWIN

#ifndef KEY

#include<conio.h>
#include<windows.h>

namespace key{

    int getkey()
    {
        int ch;
        while (1)
        {
            if (_kbhit())
            {
                ch = _getch();
                Sleep(10);
                return ch;
            }
        }
    }
}

void clear ()
{
    system ("cls");
}

#endif
#endif