#ifndef OUTPUT
#define OUTPUT

#include <thread>

inline void output ()
{
    for (int i = 1; i <= n; i ++)
    {
        for (int j = 1; j <= m; j ++)
        {
            switch (field[i][j].user)
            {
            case 0:
                // free
                printf (" ");
                break;
            
            case 1:
                // H
                printf ("H");
                break;

            case 2:
                // -
                printf ("-");
                break;
            
            case 3:
                // |
                printf ("|");
                break;
            
            case 4:
                // trigger
                printf ("*");
                break;

            default:
                printf ("?");
                break;
            } 
        }
        printf ("\n");
    }
}

void dooutput ()
{
    output ();
    msleep (OUTPUT_TIME);
    syscls ();
    if (OUTPUT_STOP == 1) return;
    dooutput ();
}

#endif