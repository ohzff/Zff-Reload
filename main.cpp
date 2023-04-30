#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <sys/stat.h>
#include <climits>

using namespace std;

#include "lib/system/data/DATA.hpp"
#include "lib/system.hpp"
#include "lib/struct-define.hpp"
#include "lib/version.hpp"

#include "lib/readworld.hpp"
#include "lib/checkdata.hpp"
#include "lib/output.hpp"
#include "lib/move.hpp"
#include "lib/endless.hpp"
#include "lib/select.hpp"

int readytorun (int &i)
{
    HIDE_CURSOR ();
    syscls ();

    thread output_thread (AdventureOutput::dooutput);
    output_thread.detach ();

    OUTPUT_STOP = 0, AdventureMove::GAMEDIED = 0, AdventureMove::GAMEWIN = 0;

    int k = AdventureMove::ctrl (i);
    if (k == -1) return 1;
    if (k != 0)
    {
        i = k - 1;
    }

    SHOW_CURSOR ();
    OUTPUT_STOP = 1;
    return 0;
}

int adventure ()
{
    int k = SelectFunc::func_select ();
    if (k == -1) return 0;
    if (k == -2)
    {
        if (check_custom_data (SelectFunc::ipt)) return 1;
        read_world (-1, string (SelectFunc::ipt));
        int a = 0;
        readytorun (a);
        return 0;
    }

    for (int i = k; i <= SelectOutput::PIDMAX; i ++)
    {
        read_world (i);
        if (readytorun (i)) break;
    }
    SHOW_CURSOR ();
    return 0;
}

int endless ()
{
    HIDE_CURSOR ();
    syscls ();

    thread output_thread (EndlessOutput::dooutput);
    output_thread.detach ();

    OUTPUT_STOP = 0, AdventureMove::GAMEDIED = 0, AdventureMove::GAMEWIN = 0;

    int k = Endless::ctrl ();
    // if (k == -1) return 1;
    SHOW_CURSOR ();
    return k;
}

int chapter_start ()
{
    int k = ChapterFunc::func_chapter ();
    if (k == -1) return 0;
    if (k == 0) return adventure ();
    if (k == 1) return endless ();
    return 0;
}

int main (int argc, char * argv[])
{
    if (argc > 1)
    {
        if (strcmp (argv[1], "version") == 0)
        {
            version_output ();
            return 0;
        }
        else
        {
            printf ("Command not found!\n");
            return 1;
        }
    }

    if (! checkdata (SelectOutput::PIDMAX))
    {
        return 1;
    }

    srand (time (NULL));

    return chapter_start ();
    // return adventure ();
}