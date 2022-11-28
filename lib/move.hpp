#ifndef MOVE_H
#define MOVE_H

inline int keyboard()
{
	return key::getkey();
}

inline int check(int num){
	if(num==72||num=='w'||num=='W')return 1;
	if(num==80||num=='s'||num=='S')return 2;
	if(num==75||num=='a'||num=='A')return 3;
	if(num==77||num=='d'||num=='D')return 4;
	if(num==10)return 13;
	if(num==114)return 7;
	if(num==112)return 8;
	if(num==113)return 9;
	if(num==27)return 27;
    if(num==32)return 32;
    if(num==224||num==-32||num == 91)return -1;
	return 0;
}

int ONJUMP = 0;
int GAMEDIED = 0;
int GAMEWIN = 0;

pair <int, int> _w;

void windowsize ()
{
    _w = getWindow ();
    WINDOW_X = _w.first - 2, WINDOW_Y = _w.second;
}

void windowsize_protect ()
{
    while (OUTPUT_STOP == 0)
    {
        windowsize ();
        msleep (OUTPUT_TIME);
    }
}

inline void stop (int type = 0)
{
    GAMEDIED = 1, OUTPUT_STOP = 1;
    if (type == 0)
    {
        syscls ();
        // MOVETO (0, 0);
        printf (" :( You died.\n");
    }
}

inline void win ()
{
    GAMEWIN = 1;
    stop (1);
    syscls ();
    // MOVETO (0, 0);
    printf (" :) You Win!\n");
}

inline bool pos_legal (int x, int y)
{
    return x > 0 && y > 0 && x <= n && y <= m;
}

void pos_legal_protect ()
{
    while (GAMEDIED == 0)
    {
        if (! pos_legal (x, y)) stop ();
        if (x == ex && y == ey) win ();
        msleep (OUTPUT_TIME);
    }
}

void trigger_enable ()
{
    for (int i = 0; i < field[x][y].trigger.size (); i ++)
    {
        int id = field[x][y].trigger[i];
        if (! trig_status[id])
        {
            trig_status[id] = true;
            if (trig_delay[id] > 0) trig_delay[id] = 0;
            else trigger[id].tmp = field[trigger[id].ctrl.x][trigger[id].ctrl.y].user;
            field[trigger[id].ctrl.x][trigger[id].ctrl.y].user = trigger[id].to;
        }
    }
}

void trigger_enable_protect ()
{
    while (GAMEDIED == 0)
    {
        trigger_enable ();
        msleep (OUTPUT_TIME);
    }
}

void do_trigger_disable (int i)
{
    if (trigger[i].ctrl.x == x && trigger[i].ctrl.y == y)
    {
        stop ();
    }
    else field[trigger[i].ctrl.x][trigger[i].ctrl.y].user = trigger[i].tmp;
}

void trigger_disable ()
{
    for (int i = 1; i <= triggerCount; i ++)
    {
        if (trig_status[i])
        {
            // do_trigger_disable (i);
            if (find(field[x][y].trigger.begin(), field[x][y].trigger.end(), i) == field[x][y].trigger.end())
            {
                trig_status[i] = false;
                if (trigger[i].delay == 0) do_trigger_disable (i);
                else
                {
                    trig_delay[i] = trigger[i].delay / 10;
                }
            }
        }
        if (trig_status[i] == false)
        {
            if (trig_delay[i] > 0)
            {
                trig_delay[i] --;
                if (trig_delay[i] <= 0) do_trigger_disable (i);
            }
        }
    }
}

void trigger_disable_protect ()
{
    while (GAMEDIED == 0)
    {
        trigger_disable ();
        msleep (OUTPUT_TIME);
    }
}

inline void move_g ()
{
    while (field[x + 1][y].issafe ())
    {
        field[x][y].user = 0;
        field[x + 1][y].user = 1;
        x ++;
        msleep (MOVEUP_TIME);
    }
}

void move_g_protect ()
{
    while (OUTPUT_STOP == 0)
    {
        if (ONJUMP == 0) move_g ();
        msleep (OUTPUT_TIME);
    }
}

void move_left_right (int t)
{
    if (field[x][y + t].issafe ())
    {
        field[x][y].user = 0;
        field[x][y + t].user = 1;
        y += t;
        // move_g ();
    }
}

void allinone_protect ()
{
    while (GAMEDIED == 0)
    {
        windowsize ();

        if (! pos_legal (x, y)) stop ();
        if (x == ex && y == ey) win ();

        trigger_disable ();
        trigger_enable ();

        msleep (OUTPUT_TIME * 10);
    }
}

void jump ()
{
    if (ONJUMP) return;
    ONJUMP = 1;
    for (int i = 1; i < 3; i ++)
    {
        if (field[x - 1][y].issafe ())
        {
            field[x][y].user = 0;
            field[x - 1][y].user = 1;
            x --;
            msleep (MOVEUP_TIME);
        }
    }
    ONJUMP = 0;
}

int ctrl ()
{
    x = sx, y = sy;
    ONJUMP = 0, GAMEDIED = 0, GAMEWIN = 0;
    strcpy (OUTPUT_RIGHT_INFO, "Level 1");

    thread allinone_thread (allinone_protect);
    // thread window_thread (windowsize_protect);
    thread g_thread (move_g_protect);
    // thread pos_thread (pos_legal_protect);
    // thread trigger_enable_thread (trigger_enable_protect);
    // thread trigger_disable_thread (trigger_disable_protect);
    allinone_thread.detach ();
    // window_thread.detach ();
    g_thread.detach ();
    // pos_thread.detach ();
    // trigger_enable_thread.detach ();
    // trigger_disable_thread.detach ();

    int read;
    while (true)
    {
        read = 0;
        while ((read < 1 || read > 4) && read != 9 && read != 32)
        {
            read = check (keyboard ());
            // read = keyverify ();
            // read = 1;
            if (GAMEDIED == 1)
            {
                read = 114514;
                break;
            }
        }
        if (read == 3 || read == 4)
        {
            //left
            move_left_right (dy[read]);
        }
        if (read == 1 || read == 32)
        {
            //jump
            // jump ();
            thread jump_thread (jump);
            jump_thread.detach ();
        }
        if (read == 9)
        {
            stop (1);
            return 0;
        }

        if (GAMEDIED == 1 || read == 114514)
        {
            return GAMEWIN;
        }
    }
}

#endif