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

char ipt[100];

int sel_command ()
{
    strcpy (ipt, "");
    while (true)
    {
        int read = keyboard ();
        if (read == 27) return 0;
        if (read == 127 && strlen (ipt) > 0)
        {
            ipt[strlen (ipt) - 1] = '\0';
            BOTTOM_LEFT_INFO[strlen (BOTTOM_LEFT_INFO) - 1] = '\0';
        }
        else if ((read >= 'a' && read <= 'z') || (read >= '0' && read <= '9') || read == ' ')
        {
            char tmp[2] = {char (read)};
            strcat (ipt, tmp);
            strcat (BOTTOM_LEFT_INFO, tmp);
        }
        else if (read == 10)
        {
            if (check_custom_data (ipt))
            {
                return 1;
            }
            else
            {
                strcpy (BOTTOM_LEFT_INFO, " Error");
                msleep (OUTPUT_TIME * 1000);
                return 0;
            }
        }
    }
    return 0;
}

int doselect ()
{
    int read;
    while (true)
    {
        read = 0;
        strcpy (BOTTOM_LEFT_INFO, " Ready");
        strcpy (BOTTOM_RIGHT_INFO, inttochar (pid + 1).c_str ());
        strcat (BOTTOM_RIGHT_INFO, "/");
        strcat (BOTTOM_RIGHT_INFO, inttochar (PIDMAX).c_str ());
        while ((read < 1 || read > 4) && read != 9 && read != 32 && read != 'l' && read != 10)
        {
            read = check (keyboard ());
        }
        if (read == 'l')
        {
            strcpy (BOTTOM_LEFT_INFO, " Load: ");
            if (sel_command () == 1)
            {
                return -2;
            }
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
    else if (k == -2) return -2;
    else return pid + 1;
}

#endif