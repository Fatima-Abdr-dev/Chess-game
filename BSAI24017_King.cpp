#include "BSAI24017_King.h"
King::King(int ri, int ci, COLOR _clr, Board* B)
	:Piece{ ri,ci,_clr,B }
{

}
void King::draw(int sr, int sc, char sym)
{
    int c = 0;
    if (this->clr == PBLACK)
        c = 2;
    else
        c = 3;
    color(c);
    gotoRowCol(sr, sc);
    cout << sym;
    gotoRowCol(sr, sc + 1);
    cout << sym;
    gotoRowCol(sr, sc + 2);
    cout << sym;
    gotoRowCol(sr, sc - 1);
    cout << sym;
    gotoRowCol(sr, sc - 2);
    cout << sym;
    gotoRowCol(sr + 1, sc);
    cout << sym;
    gotoRowCol(sr + 1, sc + 1);
    cout << sym;
    gotoRowCol(sr + 1, sc + 2);
    cout << sym;
    gotoRowCol(sr + 1, sc - 1);
    cout << sym;
    gotoRowCol(sr + 1, sc - 2);
    cout << sym;
    gotoRowCol(sr + 3, sc);
    cout << sym;
    gotoRowCol(sr + 3, sc + 1);
    cout << sym;
    gotoRowCol(sr + 3, sc + 2);
    cout << sym;
    gotoRowCol(sr + 3, sc - 1);
    cout << sym;
    gotoRowCol(sr + 3, sc - 2);
    cout << sym;
    gotoRowCol(sr + 2, sc);
    cout << sym;
    gotoRowCol(sr + 2, sc + 1);
    cout << sym;
    gotoRowCol(sr + 2, sc + 2);
    cout << sym;
    gotoRowCol(sr + 2, sc - 1);
    cout << sym;
    gotoRowCol(sr + 2, sc - 2);
    cout << sym;
    gotoRowCol(sr - 1, sc - 1);
    cout << sym;
    gotoRowCol(sr - 1, sc + 1);
    cout << sym;
    gotoRowCol(sr - 2, sc);
    cout << sym;
    gotoRowCol(sr - 2, sc + 1);
    cout << sym;
    gotoRowCol(sr - 2, sc + 2);
    cout << sym;
    gotoRowCol(sr - 2, sc - 1);
    cout << sym;
    gotoRowCol(sr - 2, sc - 2);
    cout << sym;
    gotoRowCol(sr - 3, sc);
    cout << sym;
    gotoRowCol(sr - 3, sc + 2);
    cout << sym;
    gotoRowCol(sr - 3, sc - 2);
    cout << sym;


}
bool King::islegal(Position D)
{
	int dr = abs(this->P.ri - D.ri), dc = abs(this->P.ci - D.ci);
	return ( dr==1 or dc==1 )and ((isDiagonal(this->P, D) and isDiagonalPathClear(this->B, this->P, D))
		or (isVertical(this->P, D) and isVerticalPathClear(this->B, this->P, D))
		or (isHorizontal(this->P, D) and isHorizontalPathClear(this->B, this->P, D)));
}
