#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_
#include <string>
using namespace std;

class gameBoard
{
public:
	gameBoard();
	gameBoard(int, string, int, int, bool, int);
	~gameBoard();

	void setMonopoly(int);
	int getMonopoly();

	void setSquareName(string);
	string getSquareName();

	//void setHouse(int);
	//int getHouse();
	void setSquareCost(int);
	int getSquareCost();
	
	void setSquareRent(int);
	int getSquareRent();

	void setSquareOwned(bool);
	bool getSquareOwned();

	void setOwnedBy(int);
	int getOwnedBy();

private:
	int monopoly;
	string squareName;
	int squareCost;
	//int house;
	int squareRent;
	bool squareOwned;
	int ownedBy;
};

#endif
