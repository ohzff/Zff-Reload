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

int main ()
{
    read_world (1);

    thread output_thread (dooutput);
    output_thread.detach ();
    int x = 1;
    while (x)
    {
        scanf ("%d", &x);
        printf ("%d\n", x);
    }

    OUTPUT_STOP = 1;
    return 0;
}