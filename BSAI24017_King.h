#pragma once

#include"BSAI24017_Piece.h"
class King :public Piece
{
public:
	King(int ri, int ci, COLOR _clr, Board* B);
	King(const King& k, Board* b);
	virtual void draw(int sr, int sc, char sym = -37);
	virtual bool islegal(Position D);

};



