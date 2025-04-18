#pragma once
#include"BSAI24017_Header.h"
class Board;
class Piece
{
protected:
	Position P;
	COLOR clr;
	Board* B;
	static bool isHorizontal(Position S, Position D);
	static bool isVertical(Position S, Position D);
	static bool isDiagonal(Position S, Position D);
	static bool isHorizontalPathClear(Board* B,Position S, Position D);
	static bool isVerticalPathClear(Board* B,Position S, Position D);
	static bool isDiagonalPathClear(Board* B,Position S, Position D);
public:
	Piece(int ri, int ci, COLOR _clr, Board* B);
	virtual void draw(int sr, int sc, char sym = -37) = 0;
	virtual bool islegal(Position D);
	COLOR getColor();
	Position getPositon();
	void move(Position D);
	virtual ~Piece()=default;
};

