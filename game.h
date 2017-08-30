#ifndef GAME_H
#define GAME_H
#include <string>
using namespace std;

struct property
{
	int monopolyGroup;
	bool monopoly;
	string squareName;
	int squareCost;
	int house;
	int hotel;
	int squareRent;
	bool squareOwned;
	int ownedBy;
	//functions
	property();
	property(int, bool, string, int, int, int, int, bool, int);

	void setMonopolyGroup(int);
	int getMonopolyGroup();

	void setMonopoly(bool);
	bool getMonopoly();

	void setPropertyName(string);
	string getPropertyName();

	void setHouse(int);
	int getHouse();

	void setHotel(int);
	int getHotel();

	void setPropertyCost(int);
	int getPropertyCost();
	
	void setPropertyRent(int);
	int getPropertyRent();

	void setPropertyOwned(bool);
	bool getPropertyOwned();

	void setOwnedBy(int);
	int getOwnedBy();
};
#endif
