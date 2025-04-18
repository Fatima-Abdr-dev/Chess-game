#pragma once
#include"BSAI24017_Piece.h"
class Pawn:public Piece
{
public:
	Pawn(int ri, int ci, COLOR _clr, Board* B);
	Pawn(const Pawn& P, Board* b);
	virtual void draw(int sr, int sc, char sym = -37);
	virtual bool islegal(Position D);
	bool  isopponentPeice(Board* B, Position D);

};

