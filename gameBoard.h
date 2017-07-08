#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_
#include <string>
using namespace std;

class gameBoard
{
public:
	gameBoard();
	gameBoard(string, int, int, bool);
	~gameBoard();

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

private:
	int square;
	string squareName;
	int squareCost;
	//int house;
	int squareRent;
	bool squareOwned;

};

#endif
