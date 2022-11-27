#ifndef OUTPUT
#define OUTPUT

#include <thread>

int WINDOW_X, WINDOW_Y;

/*
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

            case 5:
                // End
                printf ("#");
                break;

            default:
                printf ("?");
                break;
            } 
        }
        printf ("\n");
    }
}

*/

inline void print (int i, int j)
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

    case 5:
        // End
        printf ("#");
        break;

    default:
        printf ("?");
        break;
    } 
}

inline void output ()
{
    printf (" :) ");
    for (int i = 1; i <= WINDOW_Y - 5 - strlen (OUTPUT_RIGHT_INFO); i ++) printf (" ");
    printf ("%s \n", OUTPUT_RIGHT_INFO);
    if (WINDOW_X == 0 || WINDOW_Y == 0) return;
    int wstartx, wstarty, wendx, wendy, wwaitx, wwaity;
    if (WINDOW_X >= n)
    {
        wstartx = 1, wendx = n;
        wwaitx = (WINDOW_X - n) >> 1;
    }
    else
    {
        wstartx = x - (WINDOW_X >> 1), wendx = WINDOW_X + wstartx - 1;
        wwaitx = 0;
    }
    if (WINDOW_Y >= m)
    {
        wstarty = 1, wendy = m;
        wwaity = (WINDOW_Y - m) >> 1;
    }
    else 
    {
        wstarty = y - (WINDOW_Y >> 1), wendy = WINDOW_Y + wstarty - 1;
        wwaity = 0;        
    }
    for (int i = 1; i <= wwaitx; i ++) {
        for (int j = 1; j <= WINDOW_Y; j ++) printf (" ");
        printf ("\n");
    }
    for (int i = wstartx; i <= wendx; i ++)
    {
        if (i <= 0 || i > n)
        {
            for (int j = 1; j < WINDOW_Y; j ++) printf (" ");
            printf ("\n");
            continue;
        } 
        for (int j = 1; j <= wwaity; j ++) printf (" ");
        for (int j = wstarty; j <= wendy; j ++)
        {
            if (j <= 0 || j > m)
            {
                printf (" ");
                continue;
            }
            print (i, j);
        }
        for (int j = 1; j <= wwaity; j ++) printf (" ");
        printf ("\n");
    }
    for (int i = 1; i <= wwaitx; i ++) {
        for (int j = 1; j <= WINDOW_Y; j ++) printf (" ");
        printf ("\n");
    }
    for (int i = 1; i <= WINDOW_Y; i ++) printf (" ");
}

void dooutput ()
{
    while (OUTPUT_STOP == 0)
    {
        MOVETO (0, 0);
        output ();
        msleep (OUTPUT_TIME);
        // syscls ();
    }
}

#endif