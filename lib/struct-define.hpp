#ifndef STRUCTDEF
#define STRUCTDEF

#include <vector>
using namespace std;
const int inf = 1005;

const int dx[5] = {0, -1, 1, 0, 0};
const int dy[5] = {0, 0, 0, -1, 1};

class Pos
{
    public:
    int x, y;
    Pos () {}
    Pos (int _x, int _y) {x = _x, y = _y;}
};

class Trigger
{
    public:
    int id; // trigger id
    Pos pos; // trigger pos
    Pos ctrl; // control pos
};


class Point
{
    public:
    int user; // used by ID
    vector <int> trigger;
    vector <int> ctrlby;

    bool isfree ()
    {
        return user == 0 && trigger.size () == 0;
    }

    bool issafe ()
    {
        return user == 0;
    }
};

/*
USED id:
0. free
1. H
2. -
3. |
4. Trigger
...
*/

int n, m, sx, sy, ex, ey, triggerCount = 0;
Point field[inf][inf];
Trigger trigger[inf * 10];

int OUTPUT_STOP = 0;

#endif