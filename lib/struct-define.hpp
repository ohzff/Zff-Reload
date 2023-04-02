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
    int tmp; // control id
    int to; // control it to
    int delay; // close delay
};


class Point
{
    public:
    int user; // used by ID
    vector <int> trigger;
    vector <int> ctrlby;

    bool isfree ()
    {
        return user == 0;
    }

    bool issafe ()
    {
        return user == 0 || user == 5;
    }
};

/*
USED id:
0. free
1. H
2. -
3. |
4. Trigger
5. End
...
*/

int n, m, sx, sy, ex, ey, triggerCount = 0;
Point field[inf][inf];
Trigger trigger[inf * 10];
bool trig_status[inf * 10];
int trig_delay[inf * 10];
int x, y;
char OUTPUT_RIGHT_INFO[1000], BOTTOM_LEFT_INFO[1000], BOTTOM_RIGHT_INFO[1000];

int OUTPUT_STOP = 0, SEL_OUTPUT_STOP = 0, CHAPTER_OUTPUT_STOP = 0, ENDLESS_OUTPUT_STOP = 0;

int endless_field[10][inf];

inline string getdatapath (char *x)
{
    string str = DATAPATH;
    str = str + x;
    return str;
}

inline string getdatapath (const char x[])
{
    string str = DATAPATH;
    str = str + x;
    return str;
}

#endif