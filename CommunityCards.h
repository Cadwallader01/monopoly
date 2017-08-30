#ifndef COMMUNITYCARDS_H
#define COMMUNITYCARDS_H
#include <string>
using namespace std;

struct CommunityCards{
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
#endif
