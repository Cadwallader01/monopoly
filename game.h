#ifndef GAME_H
#define GAME_H
#include <string>
using namespace std;

struct property{
	int monopoly;
	string squareName;
	int squareCost;
	//int house;
	int squareRent;
	bool squareOwned;
	int ownedBy;
	//functions
	property();
	property(int, string, int, int, bool, int);

	void setMonopoly(int);
	int getMonopoly();

	void setPropertyName(string);
	string getPropertyName();

	//void setHouse(int);
	//int getHouse();
	void setPropertyCost(int);
	int getPropertyCost();
	
	void setPropertyRent(int);
	int getPropertyRent();

	void setPropertyOwned(bool);
	bool getPropertyOwned();

	void setOwnedBy(int);
	int getOwnedBy();
};

struct CommunityCards
{
	string card;
	int moneyOwed;
	int moneyPaid;
	int playerPosition;

	CommunityCards();
	CommunityCards(string, int, int, int);

	void setCard(string);
	string getCard();

	int getMoneyOwed();
	int getMoneyPaid();

	void setPlayerPosition(int p);
	int getPlayerPosition();
};
struct chanceCards
{
	string card;
	int moneyOwed;
	int moneyPaid;

	chanceCards();
	chanceCards(string, int, int);

	void setCard(string);
	string getCard();

	int getMoneyOwed();
	int getMoneyPaid();
};

#endif
