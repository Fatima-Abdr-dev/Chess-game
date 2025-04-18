#include "BSAI24017_Player.h"
Player::Player(string _name):name{_name}
{

}
Player::Player()
{

}
void Player::take_name()
{
	cout << "Enter the name ";
	cin >> name;
}
string Player::get_name()
{
	return name;
}
COLOR Player::get_color()
{
	return clr;
}
void Player::display_message()
{
	gotoRowCol(5, 130);
	cout << name << "! Take your turn";
}
void Player::set_clr(COLOR c)
{
	clr = c;
}