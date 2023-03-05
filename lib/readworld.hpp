#ifndef READWORLD
#define READWORLD

#include <cstring>
#include "struct-define.hpp"

const char readpath[100] = "usr/world/";
const char custompath[100] = "usr/custom/world/";

inline string inttochar (int x)
{
    return to_string (x);
}

void read_world (int id, string custom = "")
{
    string mainpath, worldpath, triggerpath;

    if (id == -1)
    {
        mainpath = getdatapath (custompath) + custom + "/main";
        worldpath = getdatapath (custompath) + custom + "/world";
        triggerpath = getdatapath (custompath) + custom + "/trigger";
    }
    else
    {
        mainpath = getdatapath (readpath) + inttochar (id) + "/main";
        worldpath = getdatapath (readpath) + inttochar (id) + "/world";
        triggerpath = getdatapath (readpath) + inttochar (id) + "/trigger";
    }

    printf ("Reading data...\n");

    memset (trigger, 0, sizeof (trigger));
    memset (field, 0, sizeof (field));
    triggerCount = 0, OUTPUT_STOP = 0;

    printf ("%s\n", mainpath.c_str ());
    printf ("%s\n", worldpath.c_str ());
    printf ("%s\n", triggerpath.c_str ());

    freopen (mainpath.c_str (), "r", stdin);
    scanf ("%d%d", &n, &m);
    scanf ("%d%d%d%d", &sx, &sy, &ex, &ey);
    printf ("N=%d, M=%d\n", n, m);

    freopen (worldpath.c_str (), "r", stdin);
    for (int i = 1; i <= n; i ++)
    {
        for (int j = 1;j <= m; j ++)
        {
            char ch;
            scanf ("%c", &ch);
            if (ch == '\n' || ch == '\0'){ i--; break; }
            switch (ch)
            {
            case '-':
                field[i][j].user = 2;
                break;
            case '|':
                field[i][j].user = 3;
                break;
            case '*':
                field[i][j].user = 4;
                break;
            
            default:
                field[i][j].user = 0;
                break;
            } 
        }
    }

    freopen (triggerpath.c_str (), "r", stdin);
    scanf ("%d", &triggerCount);
    for (int i = 1; i <= triggerCount; i ++)
    {
        int ax, ay, bx, by, to, delay;
        scanf ("%d%d%d%d%d%d", &ax, &ay, &bx, &by, &to, &delay);
        trigger[i].id = 1;
        trigger[i].pos = Pos (ax, ay);
        trigger[i].ctrl = Pos (bx, by);
        trigger[i].to = to;
        trigger[i].delay = delay;
        trigger[i].tmp = field[bx][by].user;
        for (int j = 1; j <= 4; j ++)
        {
            if (field[ax + dx[j]][ay + dy[j]].isfree ())
                field[ax + dx[j]][ay + dy[j]].trigger.push_back (i);
        }
        field[bx][by].ctrlby.push_back (i);
    }
    

    freopen (CONPATH, "r", stdin);

    field[sx][sy].user = 1;
    field[ex][ey].user = 5;
    // exit (0);
}

#endif


/*
main:
n       m
START_x START_y
END_x   End_y

world:
world.

trigger:
n
x y ctrlx ctrly
...
*/