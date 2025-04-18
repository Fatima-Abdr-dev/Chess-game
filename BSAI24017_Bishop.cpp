#include "BSAI24017_Bishop.h"
Bishop::Bishop(int ri, int ci, COLOR _clr, Board* B)
	:Piece{ ri,ci,_clr,B }
{

}
Bishop::Bishop(const Bishop& B, Board* b):Piece(B.P.ri,B.P.ci,B.clr,b)
{

}
void Bishop::draw(int sr, int sc, char sym)
{
    int c = 0;
    if (this->clr == PBLACK)
        c = 2;
    else
        c = 3;
    color(c);
    gotoRowCol(sr + 1, sc + 1);
    cout << sym;
    gotoRowCol(sr + 1, sc - 1);
    cout << sym;
    gotoRowCol(sr, sc);
    cout << sym;
    gotoRowCol(sr, sc - 2);
    cout << sym;
    gotoRowCol(sr, sc + 2);
    cout << sym;
    gotoRowCol(sr - 1, sc - 1);
    cout << sym;
    gotoRowCol(sr - 1, sc + 1);
    cout << sym;
    gotoRowCol(sr - 2, sc);
    cout << sym;
    gotoRowCol(sr + 2, sc);
    cout << sym;
    gotoRowCol(sr + 2, sc + 1);
    cout << sym;
    gotoRowCol(sr + 2, sc - 1);
    cout << sym;
    gotoRowCol(sr + 2, sc - 2);
    cout << sym;
    gotoRowCol(sr + 2, sc + 2);
    cout << sym;
    gotoRowCol(sr + 3, sc + 1);
    cout << sym;
    gotoRowCol(sr + 3, sc + 2);
    cout << sym;
    gotoRowCol(sr + 3, sc + 3);
    cout << sym;
    gotoRowCol(sr + 3, sc - 1);
    cout << sym;
    gotoRowCol(sr + 3, sc - 2);
    cout << sym;
    gotoRowCol(sr + 3, sc - 3);
    cout << sym;
    gotoRowCol(sr + 3, sc);
    cout << sym;

}
bool Bishop::islegal(Position D)
{
	return isDiagonal(this->P,D) and isDiagonalPathClear(this->B,this->P,D);
}
