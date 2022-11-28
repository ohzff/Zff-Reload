#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <sys/stat.h>

using namespace std;

#include "lib/system.hpp"
#include "lib/struct-define.hpp"

#include "lib/readworld.hpp"
#include "lib/checkdata.hpp"
#include "lib/output.hpp"
#include "lib/move.hpp"

int main ()
{
    if (! checkdata ())
    {
        return 1;
    }

    for (int i = 1; i <= 2; i ++)
    {
        read_world (i);

        HIDE_CURSOR ();
        syscls ();

        thread output_thread (dooutput);
        output_thread.detach ();

        OUTPUT_STOP = 0, GAMEDIED = 0, GAMEWIN = 0;

        if (! ctrl (i)) break;

        SHOW_CURSOR ();
        OUTPUT_STOP = 1;
    }
    SHOW_CURSOR ();
    return 0;
}