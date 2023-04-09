#ifndef OUTPUT
#define OUTPUT

#include <thread>

int WINDOW_X, WINDOW_Y, LASTLINE;

namespace AdventureOutput
{

    inline void print (int i, int j)
    {
        switch (field[i][j].user)
        {
        case 0:
            // free
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
        
        if (kline) 
        {
            for (int i = 1; i < WINDOW_Y; i ++) putchar (' ');
            putchar ('\n');
        }
        printf ("%s", BOTTOM_LEFT_INFO);
        for (int i = strlen (BOTTOM_LEFT_INFO); i < WINDOW_Y - strlen (BOTTOM_RIGHT_INFO) - 1; i ++)
        {
            putchar (' ');
        }
        printf ("%s ", BOTTOM_RIGHT_INFO);
        
    }

    void dooutput ()
    {
        while (OUTPUT_STOP == 0)
        {
            MOVETO (0, 0);
            output ();
            msleep (OUTPUT_TIME);
        }
    }
}

namespace SelectOutput
{
    char middleout[50] = "Level Options";
    int oneline, pid, PIDMAX;
    bool kline, kcol;

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
        
        if (kline) 
        {
            for (int i = 1; i < WINDOW_Y; i ++) putchar (' ');
            putchar ('\n');
        }

        printf ("%s", BOTTOM_LEFT_INFO);
        for (int i = strlen (BOTTOM_LEFT_INFO); i < WINDOW_Y - strlen (BOTTOM_RIGHT_INFO) - 1; i ++)
        {
            putchar (' ');
        }
        printf ("%s ", BOTTOM_RIGHT_INFO);
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

}

namespace ChapterOutput
{
    const string chapter_name[5] = {"  Adventure", "  Endless"};
    int CHAPTERMAX = 2 - 1, CHAPID;
    char middleout[50] = "Chapter Select";
    #define LEN 15
    bool kline, kcol;

    void chapter_print (int i, int j)
    {
        int k = (i / 5);
        if (i % 5 == 2 && k <= CHAPTERMAX)
        {
            if (j % LEN == 0 || j % LEN == LEN - 1)
            {
                if (CHAPID != k) putchar (' ');
                else putchar ('|');
            }
            else
            {
                if (j < chapter_name[k].size ()) putchar (chapter_name[k][j]);
                else putchar (' ');
            }
        }
        else if (i % 5 == 0 || i % 5 == 4)
        {
            if (CHAPID == k && j % LEN != 0 && j % LEN != LEN - 1) putchar ('-');
            else putchar (' ');
        }
        else
        {
            if ((j % LEN == 0 || j % LEN == LEN - 1) && CHAPID == k) putchar ('|');
            else putchar (' ');
        }
    }

    inline void chapter_output ()
    {
        if (WINDOW_X == 0 || WINDOW_Y == 0) return;
        for (int i = 1; i * 2 <= WINDOW_Y - strlen (middleout); i ++) putchar (' ');
        printf ("%s", middleout);
        for (int i = 1; i * 2 <= WINDOW_Y - strlen (middleout); i ++) putchar (' ');


        int wstartx, wstarty, wendx, wendy, wwaitx, wwaity;
        if (WINDOW_X > (CHAPTERMAX + 2) * 5)
        {
            wstartx = 0, wendx = (CHAPTERMAX + 1) * 5 - 1;
            wwaitx = (WINDOW_X - (CHAPTERMAX + 1) * 5) >> 1;
            if ((WINDOW_X - (CHAPTERMAX + 1) * 5) & 1)
            {
                kline = true;
            } else kline = false;
        }
        else
        {
            wstartx = CHAPID * 5 - (WINDOW_X >> 1), wendx = WINDOW_X + wstartx - 1;
            kline = false;
            wwaitx = 0;
        }

        {
            wstarty = 0, wendy = LEN - 1;
            wwaity = (WINDOW_Y - LEN) >> 1;
        }
        
        for (int i = 1; i <= wwaitx; i ++) {
            for (int j = 1; j <= WINDOW_Y; j ++) putchar (' ');
            putchar ('\n');
        }
        for (int i = wstartx; i <= wendx; i ++)
        {
            if (i < 0 || i >= (CHAPTERMAX + 1) * 5)
            {
                for (int j = 1; j < WINDOW_Y; j ++) putchar (' ');
                putchar ('\n');
                continue;
            } 
            for (int j = 1; j <= wwaity; j ++) putchar (' ');
            for (int j = wstarty; j <= wendy; j ++)
            {
                if (j < 0 || j >= LEN)
                {
                    putchar (' ');
                    continue;
                }
                chapter_print (i, j);
            }
            for (int j = 1; j <= wwaity; j ++) putchar (' ');
            putchar ('\n');
        }
        for (int i = 1; i <= wwaitx; i ++) {
            for (int j = 1; j <= WINDOW_Y; j ++) putchar (' ');
            putchar ('\n');
        }
        
        if (kline) 
        {
            putchar ('\n');
            for (int i = 1; i < WINDOW_Y; i ++) putchar (' ');
        }

        printf ("%s", BOTTOM_LEFT_INFO);
        for (int i = strlen (BOTTOM_LEFT_INFO); i < WINDOW_Y - strlen (BOTTOM_RIGHT_INFO) - 1; i ++)
        {
            putchar (' ');
        }
        printf ("%s ", BOTTOM_RIGHT_INFO);
    }

    void chapter_dooutput ()
    {
        while (CHAPTER_OUTPUT_STOP == 0)
        {
            MOVETO (0, 0);
            chapter_output ();
            msleep (OUTPUT_TIME);
        }
    }

}

namespace EndlessOutput
{

    inline void print (int i, int j)
    {
        switch (endless_field[i][j])
        {
        case 0:
            // free
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
        
        if (kline) 
        {
            for (int i = 1; i < WINDOW_Y; i ++) putchar (' ');
            putchar ('\n');
        }
        printf ("%s", BOTTOM_LEFT_INFO);
        for (int i = strlen (BOTTOM_LEFT_INFO); i < WINDOW_Y - strlen (BOTTOM_RIGHT_INFO) - 1; i ++)
        {
            putchar (' ');
        }
        printf ("%s ", BOTTOM_RIGHT_INFO);
        
    }

    void dooutput ()
    {
        while (OUTPUT_STOP == 0)
        {
            MOVETO (0, 0);
            output ();
            msleep (OUTPUT_TIME);
        }
    }
}

#endif