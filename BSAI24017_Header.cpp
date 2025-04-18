#include"BSAI24017_Header.h"
#include<Windows.h>
#include<fstream>
#include<conio.h>
#include<math.h>
#include<time.h>
void hideConsoleCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void getRowColbyLeftClick(int& rpos, int& cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT |
        ENABLE_EXTENDED_FLAGS);
    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if (InputRecord.Event.MouseEvent.dwButtonState ==

            FROM_LEFT_1ST_BUTTON_PRESSED)

        {
            cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
            rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            break;
        }
    } while (true);
}

void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}

void color(int k)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}

void makebox(int sr, int sc, int rdim, int cdim, char sym)
{
    for (int ri = 0;ri < rdim;ri++)
    {
        for (int ci = 0;ci < cdim;ci++)
        {
            if (ri == 0 or ri == rdim - 1 or ci == 0 or ci == cdim - 1)
            {
                gotoRowCol(sr + ri, sc + ci);
                cout << sym;

            }

        }
    }
}
void boarder(int rdim, int cdim)
{
    char a = 'a';
    color(7);
    for (int ci = 0;ci < 8;ci++)
    {
        makebox(8 * 12, ci * 12, 12, 12);
        gotoRowCol(8 * rdim + rdim / 2, ci * cdim + cdim / 2);
        cout << a;
        a++;
    }
    int i = 8;
    for (int ri = 0;ri < 8;ri++)
    {
        makebox(ri * 12, 8 * 12, 12, 12);
        gotoRowCol(ri * rdim + rdim / 2, 8 * cdim + cdim / 2);
        cout << i;
        i--;
    }

}
void shapefilled(int sr, int sc, int color, char sym)
{
    for (int i = 0;i < 12;i++)
    {
        for (int c = 0;c < 12;c++)
        {
            gotoRowCol(i + sr, c + sc);
            cout << sym;
        }
        cout << endl;
    }
}

void DisplayGrid(int rdim = 12, int cdim = 12)
{
    int j = 0;
    for (int i = 0;i < 8;i++)
    {
        for (int c = 0;c < 8;c++)
        {
            if (j == 0)
            {
                if (c % 2 == 0)
                    shapefilled(i * 12, c * 12, 7);
                else
                    shapefilled(i * 12, c * 12, 7, ' ');
            }
            if (j == 1)
            {
                if (c % 2 == 1)
                    shapefilled(i * 12, c * 12, 7);
                else
                    shapefilled(i * 12, c * 12, 7, ' ');
            }
        }
        if (j == 0)
            j = 1;
        else
            j = 0;
    }
}


