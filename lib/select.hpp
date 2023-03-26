#ifndef SELECT_H
#define SELECT_H

namespace SelectFunc
{
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
            strcpy (BOTTOM_RIGHT_INFO, inttochar (SelectOutput::pid + 1).c_str ());
            strcat (BOTTOM_RIGHT_INFO, "/");
            strcat (BOTTOM_RIGHT_INFO, inttochar (SelectOutput::PIDMAX).c_str ());
            while ((read < 1 || read > 4) && read != 9 && read != 32 && read != 'l' && read != 10)
            {
                // exit (0);
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
                if (SelectOutput::pid > 0)
                {
                    SelectOutput::pid --;
                }
            }
            if (read == 4)
            {
                if (SelectOutput::pid < SelectOutput::PIDMAX - 1)
                {
                    SelectOutput::pid ++;
                }
            }
            if (read == 1)
            {
                if (SelectOutput::pid >= SelectOutput::oneline)
                {
                    SelectOutput::pid -= SelectOutput::oneline;
                }
            }
            if (read == 2)
            {
                if (SelectOutput::pid / SelectOutput::oneline < SelectOutput::PIDMAX / SelectOutput::oneline)
                {
                    SelectOutput::pid += SelectOutput::oneline;
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
        return SelectOutput::pid;
    }

    int func_select ()
    {
        HIDE_CURSOR ();
        syscls ();

        thread select_output_thread (SelectOutput::select_dooutput);
        thread select_window_thread (sel_windowsize_protect);
        select_output_thread.detach ();
        select_window_thread.detach ();

        SEL_OUTPUT_STOP = 0;
        SelectOutput::pid = 0;

        int k = doselect ();

        SHOW_CURSOR ();
        SEL_OUTPUT_STOP = 1;

        if (k == -1) return -1;
        else if (k == -2) return -2;
        else return SelectOutput::pid + 1;
    }
}

namespace ChapterFunc
{
    void chapter_windowsize_protect ()
    {
        while (CHAPTER_OUTPUT_STOP == 0)
        {
            windowsize ();
            msleep (OUTPUT_TIME);
        }
    }

    int dochapter ()
    {
        int read;
        ChapterOutput::CHAPID = 0;
        while (true)
        {
            read = 0;
            strcpy (BOTTOM_LEFT_INFO, " Zff-Reload");
            strcpy (BOTTOM_RIGHT_INFO, ZFFVERSION);
            while ((read < 1 || read > 4) && read != 9 && read != 32 && read != 'l' && read != 10)
            {
                read = check (keyboard ());
            }
            if (read == 1)
            {
                if (ChapterOutput::CHAPID > 0)
                {
                    ChapterOutput::CHAPID --;
                }
            }
            if (read == 2)
            {
                if (ChapterOutput::CHAPID < ChapterOutput::CHAPTERMAX)
                {
                    ChapterOutput::CHAPID ++;
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
        return ChapterOutput::CHAPID;
    }

    int func_chapter ()
    {
        HIDE_CURSOR ();
        syscls ();

        thread chapter_output_thread (ChapterOutput::chapter_dooutput);
        thread chapter_window_thread (chapter_windowsize_protect);
        chapter_output_thread.detach ();
        chapter_window_thread.detach ();

        CHAPTER_OUTPUT_STOP = 0;

        int k = dochapter ();

        SHOW_CURSOR ();
        CHAPTER_OUTPUT_STOP = 1;

        if (k == -1) return -1;
        else return ChapterOutput::CHAPID;
    }

}

#endif