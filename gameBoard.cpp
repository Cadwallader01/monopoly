#include "gameBoard.h"
#include <string>
#include <iostream>

int const numOfSquares = 12;
gameBoard *squares = new gameBoard[numOfSquares];

gameBoard::gameBoard()
{
	int monopoly = 0;
	string squareName = "NULL";
	int squareCost = 0;
	//int house;
	int squareRent = 0;
	bool squareOwned = false;
}
gameBoard::gameBoard(int m, string n, int c, int r, bool o, int oB)
{
	monopoly = m;
	squareName = n;
	squareCost = c;
	squareRent = r;
	squareOwned = o;
	ownedBy = oB;
}
gameBoard::~gameBoard()
{
}
void gameBoard::setMonopoly(int m)
{
	monopoly = m;
}
int gameBoard::getMonopoly()
{
	return monopoly;
}
void gameBoard::setSquareName(string s)
{
	squareName = s;
}
string gameBoard::getSquareName()
{
	return squareName;
}
//void setHouse(int);
//int getHouse();
void gameBoard::setSquareCost(int c)
{
	squareCost = c;
}
int gameBoard::getSquareCost()
{
	return squareCost;
}
void gameBoard::setSquareRent(int r)
{
	squareRent = r;
}
int gameBoard::getSquareRent()
{
	return squareRent;
}
void gameBoard::setSquareOwned(bool o)
{
	squareOwned = o;
}
bool gameBoard::getSquareOwned()
{
	return squareOwned;
}
void gameBoard::setOwnedBy(int oB)
{
	ownedBy = oB;
}
int gameBoard::getOwnedBy()
{
	return ownedBy;
}
