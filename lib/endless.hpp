#ifndef ENDLESS_H
#define ENDLESS_H

namespace Endless
{
    int ONJUMP = 0;
    int GAMEDIED = 0;

    void windowsize_protect ()
    {
        while (ENDLESS_OUTPUT_STOP == 0)
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
            printf ("\n Press any key to exit.\n");
        }
    }

    inline bool pos_legal (int x, int y)
    {
        return x > 0 && x <= 5;
    }

    void pos_legal_protect ()
    {
        while (GAMEDIED == 0)
        {
            if (! pos_legal (x, y)) stop ();
            msleep (OUTPUT_TIME);
        }
    }

    inline void move_g ()
    {
        while (endless_field[x + 1][y] == 0)
        {
            endless_field[x][y] = 0;
            endless_field[x + 1][y] = 1;
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

    void update_pos ()
    {
        strcpy (BOTTOM_RIGHT_INFO, "(");
        strcat (BOTTOM_RIGHT_INFO, inttochar (x).c_str ());
        strcat (BOTTOM_RIGHT_INFO, ", ");
        strcat (BOTTOM_RIGHT_INFO, inttochar (y).c_str ());
        strcat (BOTTOM_RIGHT_INFO, ") H");
        strcat (BOTTOM_RIGHT_INFO, inttochar (WINDOW_X).c_str ());
        strcat (BOTTOM_RIGHT_INFO, " W");
        strcat (BOTTOM_RIGHT_INFO, inttochar (WINDOW_Y).c_str ()); 
    }

    void allinone_protect ()
    {
        while (GAMEDIED == 0)
        {
            windowsize ();

            if (! pos_legal (x, y)) stop ();

            update_pos ();

            msleep (OUTPUT_TIME * 10);
        }
    }

    void jump ()
    {
        if (ONJUMP) return;
        ONJUMP = 1;
        for (int i = 1; i < 3; i ++)
        {
            if (endless_field[x - 1][y] == 0)
            {
                endless_field[x][y] = 0;
                endless_field[x - 1][y] = 1;
                x --;
                msleep (MOVEUP_TIME);
            }
            else
            {
                stop ();
            }
        }
        ONJUMP = 0;
    }

    void tokenize(std::string const &str, const char* delim,
                std::vector<std::string> &out)
    {
        char *token = strtok(const_cast<char*>(str.c_str()), delim);
        while (token != nullptr)
        {
            out.push_back(std::string(token));
            token = strtok(nullptr, delim);
        }
    }

    void command ()
    {
        while (true)
        {
            int read = keyboard ();
            if (read == 27) return;
            if (read == 127 && strlen (BOTTOM_LEFT_INFO) > 1)
            {
                BOTTOM_LEFT_INFO[strlen (BOTTOM_LEFT_INFO) - 1] = '\0';
            }
            else if ((read >= 'a' && read <= 'z') || (read >= '0' && read <= '9') || read == ' ')
            {
                char tmp[2] = {char (read)};
                strcat (BOTTOM_LEFT_INFO, tmp);
            }
            else if (read == 10)
            {
                string str (BOTTOM_LEFT_INFO);
                vector <string> arg;
                tokenize (str, " ", arg);
                if (arg[0] == "/pos")
                {
                    if (arg.size () == 3)
                    {
                        int ix, iy;
                        sscanf (arg[1].c_str (), "%d", &ix);
                        sscanf (arg[2].c_str (), "%d", &iy);
                        if (field[ix][iy].issafe () && pos_legal (ix, iy))
                        {
                            field[x][y].user = 0, field[ix][iy].user = 1;
                            x = ix, y = iy;
                            return;
                        }
                    }
                    strcpy (BOTTOM_LEFT_INFO, " Error");
                    msleep (OUTPUT_TIME * 1000);
                    return;
                }
            }
        }
    }

    int ctrl ()
    {
        x = sx, y = sy;
        ONJUMP = 0, GAMEDIED = 0;
        strcpy (OUTPUT_RIGHT_INFO, "Endless");

        thread allinone_thread (allinone_protect);
        thread g_thread (move_g_protect);
        allinone_thread.detach ();
        g_thread.detach ();

        int read;
        while (true)
        {
            strcpy (BOTTOM_LEFT_INFO, " Ready");
            read = 0;
            while ((read < 1 || read > 4) && read != 9 && read != 32 && read != '/')
            {
                read = check (keyboard ());
                if (GAMEDIED == 1)
                {
                    read = 114514;
                    break;
                }
            }
            if (read == '/')
            {
                strcpy (BOTTOM_LEFT_INFO, " /");
                command ();
            }
            strcpy (BOTTOM_LEFT_INFO, " Working...");
            // if (read == 3 || read == 4)
            // {
            //     //left
            //     move_left_right (dy[read]);
            // }
            if (read == 1 || read == 32)
            {
                //jump
                thread jump_thread (jump);
                jump_thread.detach ();
            }
            if (read == 9)
            {
                strcpy (BOTTOM_LEFT_INFO, " Exit");
                stop (1);
                return -1;
            }

            if (GAMEDIED == 1 || read == 114514)
            {
                return 0;
            }
        }
    }
}

#endif