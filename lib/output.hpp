#ifndef OUTPUT
#define OUTPUT

#include <thread>

int WINDOW_X, WINDOW_Y, LASTLINE;

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

bool kline, kcol;

inline void output ()
{
    if (WINDOW_X == 0 || WINDOW_Y == 0) return;
    printf (" :) ");
    for (int i = 1; i <= WINDOW_Y - 5 - strlen (OUTPUT_RIGHT_INFO); i ++) putchar (' ');
    printf ("%s \n", OUTPUT_RIGHT_INFO);
    int wstartx, wstarty, wendx, wendy, wwaitx, wwaity;
    if (WINDOW_X > n)
    {
        wstartx = 1, wendx = n;
        wwaitx = (WINDOW_X - n) >> 1;
        if ((WINDOW_X - n) & 1) 
        {
            kline = true;
        } else kline = false;
    }
    else
    {
        wstartx = x - (WINDOW_X >> 1), wendx = WINDOW_X + wstartx - 1;
        kline = false;
        wwaitx = 0;
    }
    if (WINDOW_Y > m)
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
            for (int j = 1; j <= WINDOW_Y; j ++) putchar (' ');
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
    for (int i = 1; i <= wwaitx; i ++) {
        for (int j = 1; j <= WINDOW_Y; j ++) putchar (' ');
        putchar ('\n');
    }
    printf ("%s", BOTTOM_LEFT_INFO);
    for (int i = strlen (BOTTOM_LEFT_INFO); i < WINDOW_Y - strlen (BOTTOM_RIGHT_INFO) - 1; i ++)
    {
        putchar (' ');
    }
    printf ("%s ", BOTTOM_RIGHT_INFO);
    if (kline) 
    {
        putchar ('\n');
        for (int i = 1; i < WINDOW_Y; i ++) putchar (' ');
    }
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

char middleout[50] = "Level Options";
int oneline, pid, PIDMAX;

void select_print (int i, int j)
{
    int k = (i / 3) * oneline + j / 5;
    if (i % 3 == 1 && k < PIDMAX)
    {
        if (j % 5 == 0 || j % 5 == 4)
        {
            if (pid != k) putchar (' ');
            else putchar ('|');
        }
        else
        {
            if (j % 5 == 1 && (k + 1) > 100)
            {
                putchar ((k + 1) / 100 + '0');
            }
            else if (j % 5 == 2 && (k + 1) > 10)
            {
                putchar (((k + 1) % 100) / 10 + '0');
            }
            else if (j % 5 == 3)
            {
                putchar (((k + 1) % 10) + '0');
            }
            else putchar (' ');
        }
    }
    else
    {
        if (pid == k && j % 5 != 0 && j % 5 != 4) putchar ('-');
        else putchar (' ');
    }
}

inline void select_output ()
{
    if (WINDOW_X == 0 || WINDOW_Y == 0) return;
    for (int i = 1; i * 2 <= WINDOW_Y - strlen (middleout); i ++) putchar (' ');
    printf ("%s", middleout);
    for (int i = 1; i * 2 <= WINDOW_Y - strlen (middleout); i ++) putchar (' ');


    int wstartx, wstarty, wendx, wendy, wwaitx, wwaity;
    oneline = (WINDOW_Y - 2) / 5;
    if (WINDOW_X > (PIDMAX / oneline + 1) * 3)
    {
        wstartx = 0, wendx = (PIDMAX / oneline + 1) * 3 - 1;
        wwaitx = (WINDOW_X - (PIDMAX / oneline + 1) * 3) >> 1;
        if ((WINDOW_X - (PIDMAX / oneline + 1) * 3) & 1)
        {
            kline = true;
        } else kline = false;
    }
    else
    {
        wstartx = pid / oneline * 3 - (WINDOW_X >> 1), wendx = WINDOW_X + wstartx - 1;
        kline = false;
        wwaitx = 0;
    }

    {
        wstarty = 0, wendy = oneline * 5 - 1;
        wwaity = (WINDOW_Y - oneline * 5) >> 1;
    }
    
    for (int i = 1; i <= wwaitx; i ++) {
        for (int j = 1; j <= WINDOW_Y; j ++) putchar (' ');
        putchar ('\n');
    }
    for (int i = wstartx; i <= wendx; i ++)
    {
        if (i < 0 || i >= (PIDMAX / oneline + 1) * 3)
        {
            for (int j = 1; j < WINDOW_Y; j ++) putchar (' ');
            putchar ('\n');
            continue;
        } 
        for (int j = 1; j <= wwaity; j ++) putchar (' ');
        for (int j = wstarty; j <= wendy; j ++)
        {
            if (j < 0 || j >= oneline * 5)
            {
                putchar (' ');
                continue;
            }
            select_print (i, j);
        }
        for (int j = 1; j <= wwaity; j ++) putchar (' ');
        putchar ('\n');
    }
    for (int i = 1; i <= wwaitx; i ++) {
        for (int j = 1; j <= WINDOW_Y; j ++) putchar (' ');
        putchar ('\n');
    }

    printf ("%s", BOTTOM_LEFT_INFO);
    for (int i = strlen (BOTTOM_LEFT_INFO); i < WINDOW_Y - strlen (BOTTOM_RIGHT_INFO) - 1; i ++)
    {
        putchar (' ');
    }
    printf ("%s ", BOTTOM_RIGHT_INFO);
    if (kline) 
    {
        putchar ('\n');
        for (int i = 1; i < WINDOW_Y; i ++) putchar (' ');
    }
}

void select_dooutput ()
{
    while (SEL_OUTPUT_STOP == 0)
    {
        MOVETO (0, 0);
        select_output ();
        msleep (OUTPUT_TIME);
    }
}

#endif