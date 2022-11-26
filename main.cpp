#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "lib/system.hpp"
#include "lib/struct-define.hpp"

#include "lib/readworld.hpp"
#include "lib/output.hpp"
#include "lib/move.hpp"

int main ()
{
    read_world (1);

    HIDE_CURSOR ();
    syscls ();

    thread output_thread (dooutput);
    output_thread.detach ();
    // int x = 1;
    // while (x)
    // {
    //     scanf ("%d", &x);
    //     printf ("%d\n", x);
    // }

    ctrl ();

    RESET_CURSOR ();
    OUTPUT_STOP = 1;
    return 0;
}