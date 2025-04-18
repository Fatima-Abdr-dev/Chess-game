#include "BSAI24017_Piece.h"
#include"BSAI24017_Board.h"
Piece::Piece(int ri, int ci, COLOR _clr, Board* b)
	:P{ ri,ci }, clr{ _clr }, B{ b }
{

}
bool Piece::islegal(Position D)
{
	return true;
}

Piece::Piece(Piece* Pi)
{
	this->B = new Board(*Pi->B);
	this->clr = Pi->clr;
	this->P = Pi->P;
}
COLOR Piece::getColor()
{
	if (this)
		return clr;
	else
		return NONE;
}
Position Piece::getPositon()
{
	if (this)
	return P;
}
void Piece::move(Position D)
{
	P = D;
	
}
bool Piece::isHorizontal(Position S, Position D)
{
	return S.ri == D.ri;
}
bool Piece::isVertical(Position S, Position D)
{
	return S.ci == D.ci;
}
bool Piece::isDiagonal(Position S, Position D)
{
	int dr = abs(S.ri - D.ri);
	int dc = abs(S.ci - D.ci);
	return dr == dc;
}
bool Piece::isHorizontalPathClear(Board* B, Position S, Position D)
{
	int s = 0, e = 0;
	if (D.ci > S.ci)
	{
		s = S.ci + 1;
		e = D.ci - 1;
	}
	else
	{
		s = D.ci + 1;
		e = S.ci - 1;
	}
	for (int c = s;c <= e;c++)
	{
		if (B->PieceAt({ S.ri,c }) != nullptr)
			return false;
	}
	return true;
}
bool Piece::isVerticalPathClear(Board* B, Position S, Position D)
{
	int s = 0, e = 0;
	if (D.ri > S.ri)
	{
		s = S.ri + 1;
		e = D.ri - 1;
	}
	else
	{
		s = D.ri + 1;
		e = S.ri - 1;
	}
	for (int c = s;c <= e;c++)
	{
		if (B->PieceAt({c,S.ci }) != nullptr)
			return false;
	}
	return true;
}
bool Piece::isDiagonalPathClear(Board* B, Position S, Position D)
{
	int dr = D.ri - S.ri;
	int dc = D.ci - S.ci;
	int d = 0;
	if (dr > 0 and dc > 0)//Top left to bottom right
	{
		d = D.ri - S.ri - 1;
		for (int i = 1;i <= d;i++)
		{
			if (B->PieceAt({ S.ri + i,S.ci + i }) != nullptr)
			{
				return false;
			}
		}
	}
	else if (dr < 0 and dc < 0)//Bottom right to top left
	{
		d = S.ri - D.ri - 1;
		for (int i = 1;i <= d;i++)
		{
			if (B->PieceAt({ S.ri - i,S.ci - i }) != nullptr)
			{
				return false;
			}
		}
	}
	else if (dr < 0 and dc > 0)//bottom left to top right
	{
		d = D.ci - S.ci - 1;
		for (int i = 1;i <= d;i++)
		{
			if (B->PieceAt({ S.ri - i,S.ci + i }) != nullptr)
			{
				return false;
			}
		}
	}
	else if(dr > 0 and dc < 0)//top right to bottom left
	{
		d = D.ri - S.ri - 1;
		for (int i = 1;i <= d;i++)
		{
			if (B->PieceAt({ S.ri + i,S.ci - i }) != nullptr)
			{
				return false;
			}
		}
	}
	return true;
}