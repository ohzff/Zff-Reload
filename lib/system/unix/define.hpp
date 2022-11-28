#include <cstdlib>
#include <stdio.h>
#include <sys/ioctl.h>

void syscls ()
{
    system ("clear");
}


const char CONPATH[20] = "/dev/tty";

#define OUTPUT_TIME 1000
#define MOVEUP_TIME 100000
#define TIMEDIV 1

void msleep (long x)
{
    usleep (x);
}

// SYS way

//清屏
#define CLEAR() printf("\033[2J")
 
// 上移光标
#define MOVEUP(x) printf("\033[%dA", (x))
 
// 下移光标
#define MOVEDOWN(x) printf("\033[%dB", (x))
 
// 左移光标
#define MOVELEFT(y) printf("\033[%dD", (y))
 
// 右移光标
#define MOVERIGHT(y) printf("\033[%dC",(y))
 
// 定位光标
#define MOVETO(x,y) printf("\033[%d;%dH", (x), (y))
 
// 光标复位
// #define RESET_CURSOR() printf("\033[H")
// 隐藏光标
#define HIDE_CURSOR() printf("\033[?25l")
 
// 显示光标
#define SHOW_CURSOR() printf("\033[?25h")
 
//清除从光标到行尾的内容
#define CLEAR_LINE() printf("\033[K")
//反显
#define HIGHT_LIGHT() printf("\033[7m")
#define UN_HIGHT_LIGHT() printf("\033[27m")
 
//设置颜色
#define SET_FRONT_COLOR(color) printf("\033[%dm",(color))
#define SET_BACKGROUND_COLOR(color) printf("\033[%dm",(color))
//前景色
#define FRONT_BLACK 30
#define FRONT_RED 31
#define FRONT_GREEN 32
#define FRONT_YELLOW 33
#define FRONT_BLUE 34
#define FRONT_PURPLE 35
#define FRONT_DEEP_GREEN 36
#define FRONT_WHITE 37
 
//背景色
#define BACKGROUND_BLACK 40
#define BACKGROUND_RED 41
#define BACKGROUND_GREEN 42
#define BACKGROUND_YELLOW 43
#define BACKGROUND_BLUE 44
#define BACKGROUND_PURPLE 45
#define BACKGROUND_DEEP_GREEN 46
#define BACKGROUND_WHITE 47

struct winsize w;

pair <int, int> getWindow ()
{
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return pair <int,int> (w.ws_row, w.ws_col);
}

#define putchar(x) putchar_unlocked(x)
