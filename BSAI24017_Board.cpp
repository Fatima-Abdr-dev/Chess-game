#include "BSAI24017_Board.h"
#include"BSAI24017_Header.h"
#include<fstream>
bool is_Castling = false;
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
Board::Board() :Turn{ PBLACK },Ps{nullptr},legal_board{false}
{
	init();
}
void Board::init()
{
	initialize_with_false();
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
	/*if (is_Castling and Ps[S.ri][S.ci]!=nullptr)
	{
		Ps[S.ri][S.ci]->draw(S.ri * 12 + 12 / 2, S.ci * 12 + 12 / 2);
	}*/
	color(7);


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
			if ( isValidDestination({ i,c }) and Ps[S.ri][S.ci]->islegal({ i,c }))
			{
				this->Copying(Copy_Board);
				Copy_Board.Ps[S.ri][S.ci]->move({ i,c });
				Copy_Board.update({ S.ri,S.ci }, { i,c });
				if (!Copy_Board.is_selfcheck())
				{
					this->legal_board[i][c] = true;
				}
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
							this->Copying(Copy_Board);
							Copy_Board.update({ ri,ci }, { r,c });
							if (!Copy_Board.is_selfcheck())
							{
								change_turn();
								return false;
							}
						}
					}

				}
			}
		}
	}
	change_turn();
	return true;
}
void Board::Copying(Board &Copy_Board)
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
				Copy_Board.Ps[i][c] = new King(*K, & Copy_Board);
			else if (Q)
				Copy_Board.Ps[i][c] = new Queen(*Q, &Copy_Board);
			else if (H)
				Copy_Board.Ps[i][c] = new Horse(*H, &Copy_Board);
			else if (P)
				Copy_Board.Ps[i][c] = new Pawn(*P, &Copy_Board);
			else if (B)
				Copy_Board.Ps[i][c] = new Bishop(*B, &Copy_Board);
			else if (R)
				Copy_Board.Ps[i][c] = new Rook(*R, &Copy_Board);
			else 
				Copy_Board.Ps[i][c] = nullptr;
		}
	}
	Copy_Board.Turn = this->Turn;
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
							this->Copying(Copy_Board);
							Copy_Board.Ps[ri][ci]->move({ r,c });
							Copy_Board.update({ri,ci}, {r,c});
							if (!Copy_Board.is_selfcheck())
							{
								change_turn();
								return false;
							}
						}
					}

				}
			}
		}
	}
	change_turn();
	return true;

}
void menu()
{
	int rows = 120, cols = 200;
	int r = rows * 0.65, c = cols * 0.65;
	gotoRowCol(r, c);
	cout << "1.Queen" << endl;
	cout << endl;
	gotoRowCol(r + 1, c);
	cout << "2.Rook" << endl;
	cout << endl;
	gotoRowCol(r + 2, c);
	cout << "3.Horse" << endl;
	cout << endl;
	gotoRowCol(r + 3, c);
	cout << "4.Bishop" << endl;
	cout << endl;
	gotoRowCol(r + 4, c);
	cout << "5.Me Razi hon Pawn per" << endl;
}
void Board::Switchcase(int choice, Position P, COLOR _T)
{
	int rows = 120, cols = 200;
	int r = rows * 0.65, c = cols * 0.65;
	switch (choice)
	{
	case 1:
		if (Ps[P.ri][P.ci] != nullptr)
			delete Ps[P.ri][P.ci];
		this->Ps[P.ri][P.ci] = new Queen(P.ri, P.ci, _T, this);
		gotoRowCol(r, c);
		cout << "          " << endl;
		cout << endl;
		gotoRowCol(r + 1, c);
		cout << "           " << endl;
		cout << endl;
		gotoRowCol(r + 2, c);
		cout << "           " << endl;
		cout << endl;
		gotoRowCol(r + 3, c);
		cout << "          " << endl;
		cout << endl;
		gotoRowCol(r + 4, c);
		cout << "                     " << endl;
		break;
	case 2:
		if (Ps[P.ri][P.ci] != nullptr)
			delete Ps[P.ri][P.ci];
		this->Ps[P.ri][P.ci] = new Rook(P.ri, P.ci, _T, this);
		gotoRowCol(r, c);
		cout << "         " << endl;
		cout << endl;
		gotoRowCol(r + 1, c);
		cout << "		 " << endl;
		cout << endl;
		gotoRowCol(r + 2, c);
		cout << "			  " << endl;
		cout << endl;
		gotoRowCol(r + 3, c);
		cout << "			" << endl;
		cout << endl;
		gotoRowCol(r + 4, c);
		cout << "				          " << endl;
		break;
	case 3:
		if (Ps[P.ri][P.ci] != nullptr)
			delete Ps[P.ri][P.ci];
		this->Ps[P.ri][P.ci] = new Horse(P.ri, P.ci, _T, this);
		gotoRowCol(r, c);
		cout << "			" << endl;
		cout << endl;
		gotoRowCol(r + 1, c);
		cout << "			" << endl;
		cout << endl;
		gotoRowCol(r + 2, c);
		cout << "				" << endl;
		cout << endl;
		gotoRowCol(r + 3, c);
		cout << "			 " << endl;
		cout << endl;
		gotoRowCol(r + 4, c);
		cout << "				          " << endl;
		break;
	case 4:
		if (Ps[P.ri][P.ci] != nullptr)
			delete Ps[P.ri][P.ci];
		this->Ps[P.ri][P.ci] = new Bishop(P.ri, P.ci, _T, this);
		gotoRowCol(r, c);
		cout << "		    " << endl;
		cout << endl;
		gotoRowCol(r + 1, c);
		cout << "			" << endl;
		cout << endl;
		gotoRowCol(r + 2, c);
		cout << "				" << endl;
		cout << endl;
		gotoRowCol(r + 3, c);
		cout << "					" << endl;
		cout << endl;
		gotoRowCol(r + 4, c);
		cout << "						  " << endl;
		break;
	case 5:
		gotoRowCol(r, c);
		cout << "				" << endl;
		cout << endl;
		gotoRowCol(r + 1, c);
		cout << "		 " << endl;
		cout << endl;
		gotoRowCol(r + 2, c);
		cout << "			   " << endl;
		cout << endl;
		gotoRowCol(r + 3, c);
		cout << "			  " << endl;
		cout << endl;
		gotoRowCol(r + 4, c);
		cout << "                     " << endl;
		break;
	}
}
void Board::Promotion()
{
	int choice = 0;
	for (int ri = 0;ri < 8;ri++)
	{
		for (int ci = 0;ci < 8;ci++)
		{
			Pawn* P = dynamic_cast<Pawn*>(Ps[ri][ci]);
			if (P and ri == 0 and P->getColor()==PWHITE)
			{
				menu();
				cin>>choice;
				Switchcase(choice, { ri,ci }, PWHITE);
				return;
			}
			else if (P and ri == 7 and P->getColor() == PBLACK)
			{
				menu();
				cin >> choice;
				Switchcase(choice, { ri,ci }, PWHITE);
				return;
			}
		}
	}
}
bool Board::isPromotion()
{
	for (int ci = 0;ci < 8;ci++)
	{
		Pawn* P = dynamic_cast<Pawn*>(Ps[0][ci]);
		if (P and P->getColor() == Turn)
			return true;
	}
	for (int ci = 0;ci < 8;ci++)
	{
		Pawn* P = dynamic_cast<Pawn*>(Ps[7][ci]);
		if (P and P->getColor() == Turn)
			return true;
	}
	return false;
}
void Board::save_in_file()
{
	ofstream wr("Board.txt");
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
			{
				if (K->getColor() == PBLACK)
					wr << "K";
				else
					wr << "k";
			}
			else if (Q)
			{
				if (Q->getColor() == PBLACK)
					wr << "Q";
				else
					wr << "q";
			}
			else if (H)
			{
				if (H->getColor() == PBLACK)
					wr << "H";
				else
					wr << "h";
			}
			else if (P)
			{
				if (P->getColor() == PBLACK)
					wr << "P";
				else
					wr << "p";
			}
			else if (B)
			{
				if (B->getColor() == PBLACK)
					wr << "B";
				else
					wr << "b";
			}
			else if (R)
			{
				if (R->getColor() == PBLACK)
					wr << "R";
				else
					wr << "r";
			}
			else
				wr << "_";
		}
	}
	if (Turn == PBLACK)
		wr << 0;
	else
		wr << 1;
}
void Board::read_from_file()
{
	ifstream rd("Board.txt");
	char sym=0;
	for (int i = 0;i < 8;i++)
	{
		for (int c = 0;c < 8;c++)
		{
			rd >> sym;
			switch (sym)
			{
			case 'K':
				this->Ps[i][c] = new King(i, c, PBLACK, this);
				break;
			case 'Q':
				this->Ps[i][c] = new Queen(i, c, PBLACK, this);
				break;
			case 'H':
				this->Ps[i][c] = new Horse(i, c, PBLACK, this);
				break;
			case 'B':
				this->Ps[i][c] = new Bishop(i, c, PBLACK, this);
				break;
			case 'R':
				this->Ps[i][c] = new Rook(i, c, PBLACK, this);
				break;
			case 'P':
				this->Ps[i][c] = new Pawn(i, c, PBLACK, this);
				break;
			case 'k':
				this->Ps[i][c] = new King(i, c, PWHITE, this);
				break;
			case 'q':
				this->Ps[i][c] = new Queen(i, c, PWHITE, this);
				break;
			case 'h':
				this->Ps[i][c] = new Horse(i, c, PWHITE, this);
				break;
			case 'b':
				this->Ps[i][c] = new Bishop(i, c, PWHITE, this);
				break;
			case 'r':
				this->Ps[i][c] = new Rook(i, c, PWHITE, this);
				break;
			case 'p':
				this->Ps[i][c] = new Pawn(i, c, PWHITE, this);
				break;
			default:
				this->Ps[i][c] = nullptr;
				break;
			}
		}
	}
	rd >> sym;
	if (sym == 1)
	{
		Turn = PWHITE;
	}
	else
		Turn = PBLACK;
}
void Board::FindRook(Position& R)
{
	for (int i = 0;i < 8;i++)
	{
		for (int c = 0;c < 8;c++)
		{
			Rook* Ki = dynamic_cast<Rook*> (Ps[i][c]);
			if (Ki and Ki->getColor() == Turn)
			{
				R.ri = i;
				R.ci = c;
			}
		}
	}
}
bool Board::is_Castling_Possible(Position &R)
{
	Rook* R1{};
	Rook* R2{};
	Position K;
	IsOpponentKing(K);
	if (Turn == PBLACK)
	{
		R1 = dynamic_cast<Rook*>(Ps[0][0]);
		R2 = dynamic_cast<Rook*>(Ps[0][7]);
		if (R1)
		{
			R = { R1->getPositon() };
			if (Ps[K.ri][K.ci]->castling(R, this))
			{
				is_Castling = true;
				return true;
			}
		}
		if (R2)
		{
			R = { R2->getPositon() };
			if (Ps[K.ri][K.ci]->castling(R, this))
			{
				is_Castling = true;
				return true;
			}
		}
	}
	else
	{
		R1 = dynamic_cast<Rook*>(Ps[7][0]);
		R2 = dynamic_cast<Rook*>(Ps[7][7]);
		if (R1)
		{
			R = { R1->getPositon() };
			if (Ps[K.ri][K.ci]->castling(R, this))
			{
				is_Castling = true;
				return true;
			}
		}
		if (R2)
		{
			R = { R2->getPositon() };
			if (Ps[K.ri][K.ci]->castling(R, this))
			{
				is_Castling = true;
				return true;
			}
		}
	}
	return false;
}
void Board::play()
{
	int choice = 0;
	cout << "1.New Game" << endl;
	cout << "2.Saved Game" << endl;
	cout << "Enter the choice" << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
		init();
		break;
	case 2:
		read_from_file();
		break;
	}
	system("cls");
	Ply[0].take_name();
	Ply[1].take_name();
	Ply[0].set_clr(PBLACK);
	Ply[1].set_clr(PWHITE);
	system("cls");
	Position S{}, D{};
	boarder(12, 12);
	DisplayGrid(12, 12);
	this->displayBoard();
	char k = {};
	Position R;
	King* K{};
	while (true)
	{
		Ply[Turn].display_message();
		do {
			is_Castling = false;
			do
			{
				do
				{
					highlight(7);
					getCoordinates(S);
				} while (!isValidSource(S));
				compute_legal_moves(S);
				highlight(5);
				K = dynamic_cast<King*>(Ps[S.ri][S.ci]);
				if (K and this->is_Castling_Possible(R))
				{
					gotoRowCol(7, 130);
					cout << "Wants to Do Casting('Y'for Yes and 'N' for No)" << endl;
					cin >> k;
					if (k == 'Y' or k == 'y')
						is_Castling = true;
					else if (k == 'N' or k == 'n')
						is_Castling = false;
					else
						is_Castling = false;
				}
				if (is_Castling == true)
				{
					break;
				}
				getCoordinates(D);
			} while (!(isValidDestination(D)));
		} while (this->legal_board[D.ri][D.ci] == false and !is_Castling);
		highlight(7);
		if (is_Castling)
		{
			if (S.ci < R.ci)
			{
				if (Turn == PBLACK)
				{
					Ps[S.ri][S.ci]->move({ 0,6 });
					Ps[R.ri][R.ci]->move({ 0,5 });
					update(S, { 0,6 });
					this->Print_updated_board(S, {0,6});
					update(R, { 0,5 });
					this->Print_updated_board(R, {0,5});
				}
				else if (Turn == PWHITE)
				{
					Ps[S.ri][S.ci]->move({ 7,6 });
					Ps[R.ri][R.ci]->move({ 7,5 });
					update(S, { 7,6 });
					this->Print_updated_board(S, {7,6});
					update(R, { 7,5 });
					this->Print_updated_board(R,{7,5});
				}
			}
			else if (S.ci > R.ci)
			{
				if (Turn == PBLACK)
				{
					Ps[S.ri][S.ci]->move({ 0,2 });
					Ps[R.ri][R.ci]->move({ 0,3 });
					update(S, { 0,2 });
					this->Print_updated_board(S, {0,2});
					update(R, { 0,3 });
					this->Print_updated_board(R, {0,3});
				}
				else if (Turn == PWHITE)
				{
					Ps[S.ri][S.ci]->move({ 7,2 });
					Ps[R.ri][R.ci]->move({ 7,3 });
					update(S, { 7,2 });
					this->Print_updated_board(S, {7,2});
					update(R, { 7,3 });
					this->Print_updated_board(R, {7,3});
				}

			}
		}
		else
		{
			Ps[S.ri][S.ci]->move(D);
			this->update(S, D);
			this->Print_updated_board(S, D);
		}
		is_Castling = false;
		
		if (isPromotion())
		{
			Promotion();
			this->Print_updated_board(S, D);
		}
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
		if (is_check_mate())
		{
			gotoRowCol(15, 130);
			save_in_file();
			cout << "GAME OVER";
			break;
		}
		
		change_turn();
		hideConsoleCursor();
		save_in_file();
	}
}
