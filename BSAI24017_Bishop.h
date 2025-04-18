#pragma once
#include"BSAI24017_Piece.h"
class Bishop :virtual public Piece
{
public:
	Bishop(int ri, int ci, COLOR _clr, Board* B);
	virtual void draw(int sr, int sc, char sym = -37);
	virtual bool islegal(Position D);

};


