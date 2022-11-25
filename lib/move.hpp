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

int x, y;

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

void move_left_right (int t)
{
    if (field[x][y + t].issafe ())
    {
        field[x][y].user = 0;
        field[x][y + t].user = 1;
        y += t;
        move_g ();
    }
}

void jump ()
{
    for (int i = 1; i < 3; i ++)
    {
        if (field[x - 1][y].issafe ())
        {
            field[x][y].user = 0;
            field[x - 1][y].user = 1;
            x --;
            msleep (100000);
        }
    }
    move_g ();
}

void ctrl ()
{
    x = sx, y = sy;
    int read;
    while (true)
    {
        read = 0;
        while ((read < 1 || read > 4) && read != 9 && read != 32)
        {
            read = check (keyboard ());
            // read = keyverify ();
            // read = 1;
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
            OUTPUT_STOP = 1;
            return;
        }
    }
}

#endif