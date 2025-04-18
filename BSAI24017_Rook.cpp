#include "BSAI24017_Rook.h"
Rook::Rook(int ri, int ci, COLOR _clr, Board* B)
	:Piece{ ri,ci,_clr,B }
{

}
Rook::Rook(const Rook& R, Board* b):Piece(R.P.ri,R.P.ci,R.clr,b){}
void Rook::draw(int sr, int sc, char sym )
{
    int c=0;
	if (this->clr == PBLACK)
		c=2;
	else
		c=3;
    color(c);
    gotoRowCol(sr, sc);
    cout << sym;
    gotoRowCol(sr + 1, sc);
    cout << sym;
    gotoRowCol(sr - 1, sc);
    cout << sym;
    gotoRowCol(sr, sc + 1);
    cout << sym;
    gotoRowCol(sr, sc - 1);
    cout << sym;
    gotoRowCol(sr + 1, sc + 1);
    cout << sym;
    gotoRowCol(sr + 1, sc - 1);
    cout << sym;
    gotoRowCol(sr - 1, sc + 1);
    cout << sym;
    gotoRowCol(sr - 1, sc - 1);
    cout << sym;
    gotoRowCol(sr - 2, sc + 2);
    cout << sym;
    gotoRowCol(sr - 2, sc);
    cout << sym;
    gotoRowCol(sr - 2, sc - 2);
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
bool Rook::islegal(Position D)
{
	return (isVertical(this->P, D) and isVerticalPathClear(this->B, this->P, D))
		or (isHorizontal(this->P, D) and isHorizontalPathClear(this->B, this->P, D));
}
