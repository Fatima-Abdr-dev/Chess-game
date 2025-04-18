#pragma once
#include "BSAI24017_Header.h"
#include"BSAI24017_Pawn.h"
#include"BSAI24017_Rook.h"
#include"BSAI24017_Horse.h"
#include"BSAI24017_King.h"
#include"BSAI24017_Bishop.h"
#include"BSAI24017_Queen.h"
#include"BSAI24017_Player.h"
class Piece;
class Board
{
	Piece* Ps[8][8];
	COLOR Turn;
	bool legal_board[8][8];
	Player Ply[2];
	static Board b;
	static void getCoordinates(Position& P);
	bool isValidSource(Position P);
	bool isValidDestination(Position P);
	void initialize_with_false();
	void highlight(int a);
	void IsOpponentKing(Position &K);
public:
	Board();
	void play();
	void displayBoard();
	void update(Position S,Position D);
	void change_turn();
	Piece* PieceAt(Position P);
	void Print_updated_board(Position S, Position D);
	void compute_legal_moves(Position S);
	bool is_check();
	bool is_selfcheck();
	bool is_stale_mate();
	bool is_check_mate();
	void Copying(Piece* Copy_Board[8][8]);
};

