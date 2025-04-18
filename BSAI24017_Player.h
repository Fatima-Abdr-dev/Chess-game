#pragma once
#include"BSAI24017_Header.h"
class Player
{
	string name;
	COLOR clr;
public:
	Player(string _name);
	Player();
	void take_name();
	string get_name();
	COLOR get_color();
	void display_message();
	void set_clr(COLOR c);

};

