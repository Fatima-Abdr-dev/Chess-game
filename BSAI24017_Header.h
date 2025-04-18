#pragma once
#include<iostream>
struct Position
{
	int ri, ci;
};
enum COLOR {PBLACK,PWHITE,NONE};
using namespace std;

void hideConsoleCursor();
void getRowColbyLeftClick(int& rpos, int& cpos);
void gotoRowCol(int rpos, int cpos);
void color(int k);
void makebox(int sr, int sc, int rdim, int cdim, char sym = -37);
void boarder(int rdim, int cdim);
void DisplayGrid(int rdim, int cdim);
void shapefilled(int sr, int sc, int color, char sym = -37);

