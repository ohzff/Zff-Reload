#ifndef ENDLESS_H
#define ENDLESS_H

namespace Endless
{
    int ONJUMP = 0;
    int GAMEDIED = 0;
    long long GAMESCORE = 0;

    class EndlessTemplate
    {
        private:
            IngorTimer stoptimer, gentimer;
            const int TypeCount = 1;
            // Type 1
            const int GEN1[10][10] = {
                {0, 0, 0, 0, 2, 3},
                {0, 0, 0, 0, 0, 3},
                {0, 0, 0, 2, 0, 0},
                {0, 0, 2, 0, 0, 0}
            }, GEN1_COUNT = 4;
            void gen1 (int col)
            {
                int r = rand () % GEN1_COUNT;
                for (int i = 1; i <= 5; i ++)
                {
                    endless_field[i][col] = GEN1[r][i];
                }
            }

            // Type 2
            const int GEN2[10][10] = {
                {0, 0, 0, 0, 2, 2},
                {0, 0, 0, 0, 0, 2},
                {0, 0, 0, 2, 2, 2},
                {0, 0, 2, 0, 2, 0}
            }, GEN2_COUNT = 4;
            IngorTimer gen2_timer;
            void gen2 (int col)
            {
                gentimer.setlock (1, 10);
            }

        public:
            void generate (int col)
            {
                int r = gentimer.getlock ();
                if (r == -1)
                {
                    r = rand () % TypeCount;
                }
                
                switch (r)
                {
                case 0:
                    gen1 (col);
                    break;

                case 1:
                    gen2 (col);
                    break;
                
                default:
                    break;
                }

            }
    };

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
            // syscls ();
            // MOVETO (0, 0);
            printf (" :( You died.\n Your Score: %lld.\n", GAMESCORE);
            printf (" Press any key to exit.\n");
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

    void update_score ()
    {
        strcpy (BOTTOM_RIGHT_INFO, "Score ");
        strcat (BOTTOM_RIGHT_INFO, lltochar (GAMESCORE).c_str ());
        strcat (BOTTOM_RIGHT_INFO, " H");
        strcat (BOTTOM_RIGHT_INFO, inttochar (WINDOW_X).c_str ());
        strcat (BOTTOM_RIGHT_INFO, " W");
        strcat (BOTTOM_RIGHT_INFO, inttochar (WINDOW_Y).c_str ()); 
    }

    void allinone_protect ()
    {
        while (GAMEDIED == 0)
        {
            windowsize ();

            // if (! pos_legal (x, y)) stop ();

            update_score ();

            msleep (ENDLESS_JUMP);
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
                msleep (ENDLESS_JUMP);
            }
            else
            {
                stop ();
            }
        }
        ONJUMP = 0;
    }

    int genstop = 0, GENTMP = 15;
    EndlessTemplate endlesstemplate;

    inline void world_gen ()
    {
        if (++ genstop >= GENTMP)
        {
            genstop = 0;
            endlesstemplate.generate (WINDOW_Y / 2 + ENDLESS_MID);
        }
    }
    
    inline void level_gen ()
    {
        if (GAMESCORE == 1e3)
        {
            GENTMP = 13;
        }
        if (GAMESCORE == 3e3)
        {
            GENTMP = 12;
        }
        if (GAMESCORE == 1e4)
        {
            GENTMP = 11;
        }
        if (GAMESCORE == 1e5)
        {
            GENTMP = 10;
        }
        if (GAMESCORE == 1e6)
        {
            GENTMP = 9;
        }
        if (GAMESCORE == 1e7)
        {
            GENTMP = 8;
        }
    }

    void generate_protect ()
    {
        while (GAMEDIED == 0)
        {
            world_gen ();
            level_gen ();
            for (int i = 1; i <= WINDOW_Y / 2 + ENDLESS_MID; i ++)
            {
                for (int j = 1; j <= 5; j ++)
                {
                    if (endless_field[j][i] == 1)
                    {
                        if (endless_field[j][i + 1] != 0)
                        {
                            stop ();
                        }
                        else
                        {
                            endless_field[j][i - 1] = 0;
                        }
                    }
                    else
                    {
                        endless_field[j][i] = endless_field[j][i + 1];
                    }
                }
            }

            GAMESCORE ++;
            if (GAMESCORE >= LLONG_MAX - 1) GAMESCORE = 0;
            msleep (OUTPUT_TIME * 40);
        }
    }

    int ctrl ()
    {
        x = 5, y = ENDLESS_MID, n = 6, m = 2 * ENDLESS_MID;
        ONJUMP = 0, GAMEDIED = 0;
        strcpy (OUTPUT_RIGHT_INFO, "Endless");
        for (int i = 1; i <= 2 * ENDLESS_MID; i ++)
        {
            endless_field[6][i] = 2;
        }
        endless_field[5][ENDLESS_MID] = 1;

        thread allinone_thread (allinone_protect);
        thread g_thread (move_g_protect);
        thread generate_thread (generate_protect);
        allinone_thread.detach ();
        g_thread.detach ();
        generate_thread.detach ();

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
            }
            strcpy (BOTTOM_LEFT_INFO, " Working...");
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