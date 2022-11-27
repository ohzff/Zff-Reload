#ifndef READWORLD
#define READWORLD

#include <cstring>
#include "struct-define.hpp"

const char readpath[100] = "usr/world/";

char charfield[1005][1005];

char* inttochar (int x)
{
    static char str[100];
    sprintf (str, "%d", x);
    return str;
}

void read_world (int id)
{
    char main_path[200] = "";
    char world_path[200] = "";
    char trigger_path[200] = "";

    strcat (main_path, readpath);
    strcat (main_path, inttochar (id));
    strcat (main_path, "/main");

    strcat (world_path, readpath);
    strcat (world_path, inttochar (id));
    strcat (world_path, "/world");

    strcat (trigger_path, readpath);
    strcat (trigger_path, inttochar (id));
    strcat (trigger_path, "/trigger");

    printf ("%s\n", main_path);

    freopen (main_path, "r", stdin);
    scanf ("%d%d", &n, &m);
    scanf ("%d%d%d%d\n", &sx, &sy, &ex, &ey);

    freopen (world_path, "r", stdin);
    for (int i = 1; i <= n; i ++)
    {
        cin.get (charfield[i], 1005);
        printf ("%d\n", strlen (charfield[i]));
        getchar ();
        for (int j = 1; j <= m; j ++)
        {
            switch (charfield[i][j - 1])
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

    freopen (trigger_path, "r", stdin);
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