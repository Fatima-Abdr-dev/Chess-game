#pragma once
#include"BSAI24017_Bishop.h"
#include"BSAI24017_Rook.h"
class Queen:public Bishop,public Rook
{
public:
	Queen(int ri, int ci, COLOR _clr, Board* B);
	Queen(const Queen& _Q, Board* B);
	void draw(int sr, int sc, char sym = -37)override;
	bool islegal(Position D);

};

