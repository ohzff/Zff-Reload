#if defined (SYSLINUX) || defined (SYSUNIX) || defined (SYSMAC)

#define KEY

#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
namespace key{
    #define KEYCODE_R 0x43
    #define KEYCODE_L 0x44
    #define KEYCODE_U 0x41
    #define KEYCODE_D 0x42
    #define KEYCODE_Q 0x71

    int kfd = 0;
    struct termios cooked, raw;

    void quit(int sig)
    {
        (void)sig;
        tcsetattr(kfd, TCSANOW, &cooked);//在程序结束时在恢复原来的配置
    }

    int keyLoop()
    {
        char c;

        // get the console in raw mode
        tcgetattr(kfd, &cooked); // 得到 termios 结构体保存，然后重新配置终端
        memcpy(&raw, &cooked, sizeof(struct termios));
        raw.c_lflag &=~ (ICANON | ECHO);
        // Setting a new line, then end of file
        raw.c_cc[VEOL] = 1;
        raw.c_cc[VEOF] = 2;
        tcsetattr(kfd, TCSANOW, &raw);

        // get the next event from the keyboard
        if(read(kfd, &c, 1) < 0)
        {
            perror("read():");
            exit(-1);
        }

        switch(c)
        {
            case KEYCODE_L:
            // printf("LEFT\n");
            return 75;
            break;
            case KEYCODE_R:
            // printf("RIGHT\n");
            return 77;
            break;
            case KEYCODE_U:
            // printf("UP\n");
            return 72;
            break;
            case KEYCODE_D:
            // printf("DOWN\n");
            return 80;
            break;
                default:
                    // printf("value: %c = 0x%02X = %d\n", c, c, c);
                    return c;
        }
    }

    int getkey(){
        signal(SIGINT,quit);
        return keyLoop();
    }
}

#endif