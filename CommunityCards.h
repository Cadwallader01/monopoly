#ifndef COMMUNITYCARDS_H_
#define COMMUNITYCARDS_H_
#include <string>
using namespace std;

class CommunityCards
{
public:
	CommunityCards();
	CommunityCards::CommunityCards(string, int, int);
	~CommunityCards();

	void setCard(string);
	string getCard();

	void subMoneyOwed(int);
	void addMoneyPaid(int);
	int getMoneyInfo();

private:
	string card;
	int moneyOwed;
	int moneyPaid;
};
#endif
