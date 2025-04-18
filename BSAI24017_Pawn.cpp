#include "BSAI24017_Pawn.h"
#include"BSAI24017_Board.h"
Pawn::Pawn(int ri, int ci, COLOR _clr, Board* B)
	:Piece{ri,ci,_clr,B}
{

}
void Pawn::draw(int sr, int sc, char sym )
{
	int c = 0;
	if (this->clr == PBLACK)
		c = 2;
	else
		c = 3;
	color(c);
	gotoRowCol(sr, sc);
	cout << sym;
	gotoRowCol(sr + 1, sc);
	cout << sym;
	gotoRowCol(sr, sc - 1);
	cout << sym;
	gotoRowCol(sr, sc + 1);
	cout << sym;
	gotoRowCol(sr + 1, sc + 1);
	cout << sym;
	gotoRowCol(sr + 1, sc - 1);
	cout << sym;
	gotoRowCol(sr - 1, sc);
	cout << sym;
	gotoRowCol(sr + 2, sc);
	cout << sym;
	gotoRowCol(sr + 2, sc + 1);
	cout << sym;
	gotoRowCol(sr + 2, sc - 1);
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
}
bool  Pawn::isopponentPeice(Board* B,Position D)
{
	if (B->PieceAt(D) == nullptr)
	{
		return false;
	}
	return B->PieceAt(D)->getColor() != clr;
}
bool Pawn::islegal(Position D)
{
	if (clr == PBLACK)
	{
		if (P.ri > D.ri)
			return false;
		if (isDiagonal({ P.ri, P.ci }, { D.ri, D.ci }) and isopponentPeice(B, { D.ri, D.ci }) and P.ri + 1 == D.ri and (P.ci - 1 == D.ci or P.ci + 1 == D.ci))
			return true;
		if ((P.ri == 1 and (P.ri + 2 == D.ri or P.ri + 1 == D.ri)) and isVertical({ P.ri, P.ci }, { D.ri, D.ci }) and isVerticalPathClear(B, { P.ri, P.ci }, { D.ri, D.ci }) and B->PieceAt({ D.ri,D.ci }) == nullptr)
			return true;
		if (P.ri + 1 == D.ri and isVertical({ P.ri, P.ci }, { D.ri, D.ci }) and B->PieceAt({ D.ri,D.ci }) == nullptr)
			return true;
		return false;
	}
	else
	{

		if (P.ri < D.ri)
			return false;
		if (isDiagonal({ P.ri, P.ci }, { D.ri, D.ci }) and isopponentPeice(B, { D.ri, D.ci }) and P.ri - 1 == D.ri and (P.ci + 1 == D.ci or P.ci - 1 == D.ci))
			return true;
		if ((P.ri == 6 and (P.ri - 2 == D.ri or P.ri - 1 == D.ri)) and isVertical({ P.ri, P.ci }, { D.ri, D.ci }) and isVerticalPathClear(B, { P.ri, P.ci }, { D.ri, D.ci }) and B->PieceAt({ D.ri,D.ci }) == nullptr)
			return true;
		if (P.ri - 1 == D.ri and isVertical({ P.ri, P.ci }, { D.ri, D.ci }) and B->PieceAt({ D.ri,D.ci }) == nullptr)
			return true;
		return false;
	}
}
