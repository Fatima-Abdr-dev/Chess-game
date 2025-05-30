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
	static void getCoordinates(Position& P);
	bool isValidSource(Position P);
	bool isValidDestination(Position P);
	void initialize_with_false();
	void highlight(int a);
	void IsOpponentKing(Position &K);
	void Switchcase(int choice, Position P, COLOR _T);
	void save_in_file();
	void read_from_file();
	void init();
	void FindRook(Position& R);
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
	void Copying(Board &Copy_Board);
	void Promotion();
	bool isPromotion();
	bool is_Castling_Possible(Position&);
};

