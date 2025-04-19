#include "BSAI24017_King.h"
#include"BSAI24017_Board.h"
King::King(int ri, int ci, COLOR _clr, Board* B)
	:Piece{ ri,ci,_clr,B }, ismoved{ false }
{

}
King::King(const King& k, Board* b) :Piece(k.P.ri,k.P.ci,k.clr,b)
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
void King::moved()
{
    ismoved = true;
}
bool King::get_ismoved()
{
    return ismoved;
}
bool King::castling(Position D,Board* B)
{
    Rook* R=dynamic_cast<Rook*> (B->PieceAt(D));
    if (R and !R->get_ismoved() and R->getColor()==clr and isHorizontal(this->P,D) and isHorizontalPathClear(B,this->P,D))
    {
        return true;
    }
    return false;
}
