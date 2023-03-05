#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <sys/stat.h>

using namespace std;

#include "lib/system/data/DATA.hpp"
#include "lib/system.hpp"
#include "lib/struct-define.hpp"

#include "lib/readworld.hpp"
#include "lib/checkdata.hpp"
#include "lib/output.hpp"
#include "lib/move.hpp"
#include "lib/select.hpp"
#include "lib/version.hpp"

int readytorun (int &i)
{
    HIDE_CURSOR ();
    syscls ();

    thread output_thread (dooutput);
    output_thread.detach ();

    OUTPUT_STOP = 0, GAMEDIED = 0, GAMEWIN = 0;

    int k = ctrl (i);
    if (k == -1) return 1;
    if (k != 0)
    {
        i = k - 1;
    }

    SHOW_CURSOR ();
    OUTPUT_STOP = 1;
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

    if (! checkdata (PIDMAX))
    {
        return 1;
    }

    int k = func_select ();
    if (k == -1) return 0;
    if (k == -2)
    {
        if (check_custom_data (ipt)) return 1;
        read_world (-1, string (ipt));
        int a = 0;
        readytorun (a);
        return 0;
    }

    for (int i = k; i <= PIDMAX; i ++)
    {
        read_world (i);
        if (readytorun (i)) break;
    }
    SHOW_CURSOR ();
    return 0;
}