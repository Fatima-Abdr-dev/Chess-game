#include "BSAI24017_Queen.h"
Queen::Queen(int ri, int ci, COLOR _clr, Board* B)
	:Rook{ ri,ci,_clr,B }, Bishop{ ri,ci,_clr,B },Piece{ri,ci,_clr,B}
{

}
Queen::Queen(const Queen& _Q, Board* B) :Rook(_Q.P.ri, _Q.P.ci, _Q.clr, B), Bishop(_Q.P.ri, _Q.P.ci, _Q.clr, B),Piece(_Q.P.ri, _Q.P.ci, _Q.clr, B)
{

}
void Queen::draw(int sr, int sc, char sym)
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


}
bool Queen::islegal(Position D)
{
	return Bishop::islegal(D) or Rook::islegal(D);
}
