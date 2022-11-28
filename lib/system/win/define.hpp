#include <windows.h>

HANDLE hStdout;
COORD destCoord;

void syscls ()
{
    system ("cls");
}

void MOVETO (int x, int y)
{
  hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

  //position cursor at start of window
  destCoord.X = x;
  destCoord.Y = y;
  SetConsoleCursorPosition(hStdout, destCoord);
}

// void syscls()
// {
//   HANDLE                     hStdOut;
//   CONSOLE_SCREEN_BUFFER_INFO csbi;
//   DWORD                      count;
//   DWORD                      cellCount;
//   COORD                      homeCoords = { 0, 0 };

//   hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
//   if (hStdOut == INVALID_HANDLE_VALUE) return;

//   /* Get the number of cells in the current buffer */
//   if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
//   cellCount = csbi.dwSize.X *csbi.dwSize.Y;

//   /* Fill the entire buffer with spaces */
//   if (!FillConsoleOutputCharacter(
//     hStdOut,
//     (TCHAR) ' ',
//     cellCount,
//     homeCoords,
//     &count
//     )) return;

//   /* Fill the entire buffer with the current colors and attributes */
//   if (!FillConsoleOutputAttribute(
//     hStdOut,
//     csbi.wAttributes,
//     cellCount,
//     homeCoords,
//     &count
//     )) return;

//   /* Move the cursor home */
//   SetConsoleCursorPosition( hStdOut, homeCoords );
// }

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

#define HIDE_CURSOR() ShowConsoleCursor(false)
#define SHOW_CURSOR() ShowConsoleCursor(true)

const char CONPATH[20] = "CON";

#define OUTPUT_TIME 1
#define MOVEUP_TIME 100
#define TIMEDIV 10

void msleep (long x)
{
    Sleep (x);
}

CONSOLE_SCREEN_BUFFER_INFO csbi;

pair <int, int> getWindow ()
{
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return pair <int, int> (csbi.srWindow.Bottom - csbi.srWindow.Top + 1, csbi.srWindow.Right - csbi.srWindow.Left);
}

#define putchar(x) _putchar_nolock(x)
