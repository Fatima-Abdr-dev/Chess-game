#include "BSAI24017_Board.h"
#include"BSAI24017_Header.h"
void Board::getCoordinates(Position& P)
{
	getRowColbyLeftClick(P.ri, P.ci);
	P.ri /= 12;
	P.ci /= 12;
}
bool Board::isValidSource(Position P)
{
	if (Ps[P.ri][P.ci] == nullptr)
	{
		return false;
	}
	return Ps[P.ri][P.ci]->getColor() == Turn;
}
bool Board::isValidDestination(Position P)
{
	if (Ps[P.ri][P.ci]->getColor() == Turn)
	{
		return false;
	}
	if(P.ri < 0 and P.ri>=8 and  P.ci < 0 and P.ci >= 8)
		return false;
	
		return true;
}
Board::Board() :Turn{ PBLACK }
{

	for (int i = 0;i < 8;i++)
	{
		for (int c = 0;c < 8;c++)
		{
			Ps[i][c] = nullptr;
		}
	}
	Ps[0][0] = new Rook(0, 0, PBLACK, this);
	Ps[0][1] = new Horse(0, 1, PBLACK, this);
	Ps[0][2] = new Bishop(0, 2, PBLACK, this);
	Ps[0][3] = new Queen(0, 3, PBLACK, this);
	Ps[0][4] = new King(0, 4, PBLACK, this);
	Ps[0][5] = new Bishop(0, 5, PBLACK, this);
	Ps[0][6] = new Horse(0, 6, PBLACK, this);
	Ps[0][7] = new Rook(0, 7, PBLACK, this);
	Ps[7][0] = new Rook(7, 0, PWHITE, this);
	Ps[7][1] = new Horse(7, 1, PWHITE, this);
	Ps[7][2] = new Bishop(7, 2, PWHITE, this);
	Ps[7][3] = new Queen(7, 3, PWHITE, this);
	Ps[7][4] = new King(7, 4, PWHITE, this);
	Ps[7][5] = new Bishop(7, 5, PWHITE, this);
	Ps[7][6] = new Horse(7, 6, PWHITE, this);
	Ps[7][7] = new Rook(7, 7, PWHITE, this);
	for (int ci = 0;ci < 8;ci++)
	{
		Ps[1][ci] = new Pawn(1, ci, PBLACK, this);
		Ps[6][ci] = new Pawn(6, ci, PWHITE, this);
	}
}
void Board::change_turn()
{
	Turn = static_cast<COLOR>(((int)Turn + 1) % 2);
}
void Board::Print_updated_board( Position S, Position D)
{
	if ((S.ri + S.ci) % 2 == 0)
	{
		shapefilled(S.ri * 12, S.ci * 12, 7);
	}
	else
		shapefilled(S.ri * 12, S.ci * 12, 7, ' ');
	if ((D.ri + D.ci) % 2 == 0)
	{
		shapefilled(D.ri * 12, D.ci * 12, 7);
	}
	else
		shapefilled(D.ri * 12, D.ci * 12, 7, ' ');
	int c;
	if (Ps[D.ri][D.ci]->getColor() == PBLACK)
		c = 2;
	else
		c = 3;
	color(c);
	Ps[D.ri][D.ci]->draw(D.ri * 12 + 12 / 2, D.ci * 12 + 12 / 2);
	color(7);

}

void Board::play()
{
	Ply[0].take_name();
	Ply[1].take_name();
	Ply[0].set_clr(PBLACK);
	Ply[1].set_clr(PWHITE);
	system("cls");
	Position S{}, D{};
	boarder(12, 12);
	DisplayGrid(12, 12);
	this->displayBoard();
	while (true)
	{
		Ply[Turn].display_message();
		do {
			do
			{
				do
				{
					highlight(7);
					getCoordinates(S);
				} while (!isValidSource(S));
				compute_legal_moves(S);
				highlight(5);
				getCoordinates(D);
			} while (!isValidDestination(D));
		} while (this->legal_board[D.ri][D.ci]==false);
		highlight(7);
		Ps[S.ri][S.ci]->move(D);
		this->update(S, D);
		this->Print_updated_board(S,D);
		if (this->is_check())
		{
			gotoRowCol(10, 130);
			cout << "bhaoooo....you are in danger ";
		}
		else
		{
			gotoRowCol(10, 130);
			cout << "                              ";
		}
		change_turn();
		hideConsoleCursor();
	}

}
void Board::displayBoard()
{
	for (int ri = 0;ri < 8;ri++)
	{
		for (int ci = 0;ci < 8;ci++)
		{
			if (Ps[ri][ci] != nullptr)
				Ps[ri][ci]->draw(ri * 12 + 12/ 2, ci * 12+ 12/ 2);
		}
		color(7);
	}
	color(7);
}
void Board::update(Position S, Position D)
{
	if (Ps[D.ri][D.ci] != nullptr)
		delete Ps[D.ri][D.ci], Ps[D.ri][D.ci] = nullptr;
	Ps[D.ri][D.ci] = Ps[S.ri][S.ci];
	Ps[S.ri][S.ci] = nullptr;
}
Piece* Board::PieceAt(Position P)
{
	return Ps[P.ri][P.ci];
}
void Board::initialize_with_false()
{
	for (int i = 0;i < 8;i++)
	{
		for (int c = 0;c < 8;c++)
		{
			legal_board[i][c] = false;
		}
	}
}
void Board::compute_legal_moves(Position S)
{
	Board Copy_Board;
	this->initialize_with_false();
	for (int i = 0;i < 8;i++)
	{
		for (int c = 0;c < 8;c++)
		{
			if (isValidDestination({ i,c }) and Ps[S.ri][S.ci]->islegal({ i,c }))
			{
				this->Copying(Copy_Board.Ps);
				Copy_Board.update({ S.ri,S.ci }, { i,c });
				if(!Copy_Board.is_selfcheck())
					legal_board[i][c] = true;
			}
		}
	}
}
void Board::highlight(int a)
{
	color(a);
	for (int ri = 0;ri < 8;ri++)
	{
		for (int ci = 0;ci < 8;ci++)
		{
			if (legal_board[ri][ci] == true)
				makebox(ri * 12, ci * 12, 12, 12);
		}
	}
	color(7);
}
void Board::IsOpponentKing(Position &K)
{
	for (int i = 0;i < 8;i++)
	{
		for (int c = 0;c < 8;c++)
		{
			King* Ki = dynamic_cast<King*> (Ps[i][c]);
			if (Ki and Ki->getColor()==Turn)
			{
				K.ri = i;
				K.ci = c;
			}
		}
	}
}
bool Board::is_check()
{
	Position K{};
	change_turn();
	IsOpponentKing(K);
	change_turn();

	for (int ri = 0;ri < 8;ri++)
	{
		for (int ci = 0;ci < 8;ci++)
		{
			if (isValidSource({ ri, ci }) and Ps[ri][ci]->islegal(K))
				return true;
		}
	}
	return false;
}
bool Board::is_selfcheck()
{
	change_turn();
	if (is_check())
	{
		change_turn();
		return true;
	}
	else
	{
		change_turn();
		return false;
	}
}
bool Board::is_stale_mate()
{
	change_turn();
	Board Copy_Board;
	if (!this->is_selfcheck())
	{
		return false;
	}
	for (int ri = 0;ri < 8;ri++)
	{
		for (int ci = 0;ci < 8;ci++)
		{
			if (isValidSource({ ri, ci }) and Ps[ri][ci]->getColor() == Turn)
			{
				for (int r = 0;r < 8;r++)
				{
					for (int c = 0;c < 8;c++)
					{
						if (isValidDestination({ r,c }) and Ps[ri][ci]->islegal({ r, c }))
						{
							this->Copying(Copy_Board.Ps);
							Copy_Board.update({ ri,ci }, { r,c });
							if (!Copy_Board.is_selfcheck())
								return false;
						}
					}

				}
			}
		}
	}
	change_turn();
	return true;
}
void Board::Copying(Piece* Copy_Board[8][8])
{
	for (int i = 0;i < 8;i++)
	{
		for (int c = 0;c < 8;c++)
		{
			King* K = dynamic_cast<King*> (this->Ps[i][c]);
			Pawn* P = dynamic_cast<Pawn*> (this->Ps[i][c]);
			Queen* Q = dynamic_cast<Queen*> (this->Ps[i][c]);
			Bishop* B = dynamic_cast<Bishop*> (this->Ps[i][c]);
			Horse* H = dynamic_cast<Horse*> (this->Ps[i][c]);
			Rook* R = dynamic_cast<Rook*> (this->Ps[i][c]);
			if (K)
				Copy_Board[i][c] = new King(*K);
			else if (Q)
				Copy_Board[i][c] = new Queen(*Q);
			else if (H)
				Copy_Board[i][c] = new Horse(*H);
			else if (P)
				Copy_Board[i][c] = new Pawn(*P);
			else if (B)
				Copy_Board[i][c] = new Bishop(*B);
			else if (R)
				Copy_Board[i][c] = new Rook(*R);
			else 
				Copy_Board[i][c] = nullptr;
		}
	}
}
bool Board::is_check_mate()
{
	change_turn();
	Board Copy_Board;
	for (int ri = 0;ri < 8;ri++)
	{
		for (int ci = 0;ci < 8;ci++)
		{
			if (isValidSource({ri, ci}) and Ps[ri][ci]->getColor() == Turn)
			{
				for (int r = 0;r < 8;r++)
				{
					for (int c = 0;c < 8;c++)
					{
						if (isValidDestination({ r,c }) and Ps[ri][ci]->islegal({ r, c }))
						{
							this->Copying(Copy_Board.Ps);
							Copy_Board.Ps[ri][ci]->move({ r,c });
							Copy_Board.update({ri,ci}, {r,c});
							if (!Copy_Board.is_selfcheck())
								return false;
						}
					}

				}
			}
		}
	}
	change_turn();
	return true;

}