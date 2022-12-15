#ifndef SELECT_H
#define SELECT_H

void sel_windowsize_protect ()
{
    while (SEL_OUTPUT_STOP == 0)
    {
        windowsize ();
        msleep (OUTPUT_TIME);
    }
}

int doselect ()
{
    int read;
    while (true)
    {
        read = 0;
        strcpy (BOTTOM_LEFT_INFO, " Ready");
        strcpy (BOTTOM_RIGHT_INFO, inttochar (pid + 1));
        strcat (BOTTOM_RIGHT_INFO, "/");
        strcat (BOTTOM_RIGHT_INFO, inttochar (PIDMAX));
        while ((read < 1 || read > 4) && read != 9 && read != 32 && read != '/' && read != 10)
        {
            read = check (keyboard ());
        }
        if (read == 3)
        {
            if (pid > 0)
            {
                pid --;
            }
        }
        if (read == 4)
        {
            if (pid < PIDMAX - 1)
            {
                pid ++;
            }
        }
        if (read == 1)
        {
            if (pid >= oneline)
            {
                pid -= oneline;
            }
        }
        if (read == 2)
        {
            if (pid / oneline < PIDMAX / oneline)
            {
                pid += oneline;
            }
        }
        if (read == 32 || read == 10)
        {
            break;
        }
        if (read == 9)
        {
            return -1;
        }
    }
    return pid;
}

int func_select ()
{
    HIDE_CURSOR ();
    syscls ();

    thread select_output_thread (select_dooutput);
    thread select_window_thread (sel_windowsize_protect);
    select_output_thread.detach ();
    select_window_thread.detach ();

    SEL_OUTPUT_STOP = 0;

    int k = doselect ();

    SHOW_CURSOR ();
    SEL_OUTPUT_STOP = 1;

    if (k == -1) return -1;
    else return pid + 1;
}

#endif