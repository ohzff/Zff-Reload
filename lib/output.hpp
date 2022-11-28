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
                putchar (' ');
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
        putchar ('\n');
    }
}

*/

inline void print (int i, int j)
{
    switch (field[i][j].user)
    {
    case 0:
        // free
        // putchar (' ');
        putchar (' ');
        break;
    
    case 1:
        // H
        // printf ("H");
        putchar ('H');
        break;

    case 2:
        // -
        putchar ('-');
        break;
    
    case 3:
        // |
        putchar ('|');
        break;
    
    case 4:
        // trigger
        putchar ('*');
        break;

    case 5:
        // End
        putchar ('#');
        break;

    default:
        putchar ('?');
        break;
    } 
}

inline void output ()
{
    printf (" :) ");
    for (int i = 1; i <= WINDOW_Y - 5 - strlen (OUTPUT_RIGHT_INFO); i ++) putchar (' ');
    // printf ("%s \n", OUTPUT_RIGHT_INFO);
    puts (OUTPUT_RIGHT_INFO); //putchar (' '); putchar ('\n');
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
        for (int j = 1; j <= WINDOW_Y; j ++) putchar (' ');
        putchar ('\n');
    }
    for (int i = wstartx; i <= wendx; i ++)
    {
        if (i <= 0 || i > n)
        {
            for (int j = 1; j < WINDOW_Y; j ++) putchar (' ');
            putchar ('\n');
            continue;
        } 
        for (int j = 1; j <= wwaity; j ++) putchar (' ');
        for (int j = wstarty; j <= wendy; j ++)
        {
            if (j <= 0 || j > m)
            {
                putchar (' ');
                continue;
            }
            print (i, j);
        }
        for (int j = 1; j <= wwaity; j ++) putchar (' ');
        putchar ('\n');
    }
    for (int i = 1; i < wwaitx; i ++) {
        for (int j = 1; j <= WINDOW_Y; j ++) putchar (' ');
        putchar ('\n');
    }
    for (int i = 1; i <= WINDOW_Y; i ++) putchar (' ');
}


// char printarea[inf][inf][2];
// int flag;

// inline void print (int xc, int yc, int i, int j)
// {
//     switch (field[i][j].user)
//     {
//     case 0:
//         // free
//         // putchar (' ');
//         printarea[xc][yc][flag] = (' ');
//         break;
    
//     case 1:
//         // H
//         // printf ("H");
//         printarea[xc][yc][flag] = ('H');
//         break;

//     case 2:
//         // -
//         printarea[xc][yc][flag] = ('-');
//         break;
    
//     case 3:
//         // |
//         printarea[xc][yc][flag] = ('|');
//         break;
    
//     case 4:
//         // trigger
//         printarea[xc][yc][flag] = ('*');
//         break;

//     case 5:
//         // End
//         printarea[xc][yc][flag] = ('#');
//         break;

//     default:
//         printarea[xc][yc][flag] = ('?');
//         break;
//     } 
// }

// inline void output ()
// {
//     flag = !flag;
//     int xc = 1, yc = 1;
//     // printf (" :) ");
//     printarea[xc][1][flag] = ' ', printarea[xc][2][flag] = ':', printarea[xc][3][flag] = ')', printarea[xc][4][flag] = ' ';
//     yc = 5;
//     for (int i = 1; i <= WINDOW_Y - 5 - strlen (OUTPUT_RIGHT_INFO); i ++, yc ++) printarea[xc][yc][flag] = ' ';
//     // printf ("%s \n", OUTPUT_RIGHT_INFO);
//     for (int i = 0; i < strlen (OUTPUT_RIGHT_INFO); i ++, yc ++) printarea[xc][yc][flag] = OUTPUT_RIGHT_INFO[i];
//     // puts (OUTPUT_RIGHT_INFO); //putchar (' '); putchar ('\n');
//     xc++;
//     if (WINDOW_X == 0 || WINDOW_Y == 0) return;
//     int wstartx, wstarty, wendx, wendy, wwaitx, wwaity;
//     if (WINDOW_X >= n)
//     {
//         wstartx = 1, wendx = n;
//         wwaitx = (WINDOW_X - n) >> 1;
//     }
//     else
//     {
//         wstartx = x - (WINDOW_X >> 1), wendx = WINDOW_X + wstartx - 1;
//         wwaitx = 0;
//     }
//     if (WINDOW_Y >= m)
//     {
//         wstarty = 1, wendy = m;
//         wwaity = (WINDOW_Y - m) >> 1;
//     }
//     else 
//     {
//         wstarty = y - (WINDOW_Y >> 1), wendy = WINDOW_Y + wstarty - 1;
//         wwaity = 0;        
//     }
//     for (int i = 1; i <= wwaitx; i ++, xc ++) {
//         for (int j = 1; j <= WINDOW_Y; j ++) printarea[xc][j][flag] = ' ';
//         // putchar ('\n');
//     }
//     for (int i = wstartx; i <= wendx; i ++, xc ++)
//     {
//         if (i <= 0 || i > n)
//         {
//             for (int j = 1; j < WINDOW_Y; j ++) printarea[xc][j][flag] = ' ';
//             // putchar ('\n');
//             continue;
//         } 
//         for (yc = 1; yc <= wwaity; yc ++) printarea[xc][yc][flag] = ' ';
//         for (int j = wstarty; j <= wendy; j ++, yc ++)
//         {
//             if (j <= 0 || j > m)
//             {
//                 printarea[xc][yc][flag] = ' ';
//                 continue;
//             }
//             print (xc, yc, i, j);
//         }
//         for (int j = 1; j <= wwaity; j ++, yc ++) printarea[xc][yc][flag] = ' ';
//         // putchar ('\n');
//     }
//     for (int i = 1; i < wwaitx; i ++, xc ++) {
//         for (int j = 1; j <= WINDOW_Y; j ++) printarea[xc][j][flag] = ' ';
//         // putchar ('\n');
//     }
//     for (int i = 1; i <= WINDOW_Y; i ++) printarea[xc][i][flag] = ' ';

//     xc = 1, yc = 0;
//     for (int i = 1; i <= WINDOW_X; i ++)
//     {
//         for (int j = 1; j <= WINDOW_Y; j ++)
//         {
//             if (printarea[i][j][flag] != printarea[i][j][!flag])
//             {
//                 if (xc != x || yc != j - 1)
//                 {
//                     MOVETO (i, j);
//                     xc = i, yc = j;
//                 }
//                 putchar (printarea[i][j][flag]);
//             }
//         }
//     }
// }

void dooutput ()
{
    while (OUTPUT_STOP == 0)
    {
        MOVETO (0, 0);
        output ();
        msleep (OUTPUT_TIME);
        // msleep (1000000);
        // syscls ();
    }
}

#endif