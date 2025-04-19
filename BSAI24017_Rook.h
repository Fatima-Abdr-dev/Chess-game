#pragma once
#include"BSAI24017_Piece.h"
class Rook :virtual public Piece
{
	bool ismoved;
public:
	Rook(const Rook& R, Board* b);
	Rook(int ri, int ci, COLOR _clr, Board* B);
	virtual void draw(int sr, int sc, char sym = -37);
	virtual bool islegal(Position D);
	void moved();
	bool get_ismoved();
};



