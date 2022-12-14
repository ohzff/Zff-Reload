#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <sys/stat.h>

using namespace std;

#include "../system.hpp"
#include "../struct-define.hpp"

#include "../readworld.hpp"
#include "../checkdata.hpp"
#include "../output.hpp"
#include "../move.hpp"

int main (int argc, char * argv[])
{
    int i = 0;
    while (++ i)
    {
        int k = keyboard ();
        printf ("%d: %d\n", i, k);
        if (k == 'q')
        {
            break;
        }
    }
    return 0;
}