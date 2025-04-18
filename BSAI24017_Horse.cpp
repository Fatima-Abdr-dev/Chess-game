#include "BSAI24017_Horse.h"
Horse::Horse(int ri, int ci, COLOR _clr, Board* B)
	:Piece{ ri,ci,_clr,B }
{

}
Horse::Horse(const Horse& H, Board* b) :Piece(H.P.ri, H.P.ci, H.clr, b)
{

}
void Horse::draw(int sr, int sc, char sym )
{
    int c = 0;
    if (this->clr == PBLACK)
        c = 2;
    else
        c = 3;
    color(c);
    gotoRowCol(sr - 2, sc);
    cout << sym;
    gotoRowCol(sr - 1, sc + 1);
    cout << sym;
    gotoRowCol(sr, sc + 2);
    cout << sym;
    gotoRowCol(sr + 1, sc + 2);
    cout << sym;
    gotoRowCol(sr + 2, sc + 1);
    cout << sym;
    gotoRowCol(sr - 1, sc - 1);
    cout << sym;
    gotoRowCol(sr, sc - 2);
    cout << sym;
    gotoRowCol(sr + 1, sc - 2);
    cout << sym;
    gotoRowCol(sr + 2, sc - 2);
    cout << sym;
    gotoRowCol(sr + 3, sc + 1);
    cout << sym;
    gotoRowCol(sr + 3, sc + 2);
    cout << sym;
    gotoRowCol(sr + 3, sc - 1);
    cout << sym;
    gotoRowCol(sr + 3, sc - 2);
    cout << sym;
    gotoRowCol(sr + 3, sc);
    cout << sym;

}
bool Horse::islegal(Position D)
{
	int dr = D.ri - P.ri, dc = D.ci - P.ci;
	return (abs(dr) == 1 and abs(dc) == 2) or (abs(dr) == 2 and abs(dc) == 1);
}
