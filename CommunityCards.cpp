#include "CommunityCards.h"
#include <string>
#include <iostream>

CommunityCards::CommunityCards()
{
	string card = "NULL";
	int moneyOwed = 0;
	int moneyPaid = 0;
}
CommunityCards::CommunityCards(string c, int mOwed, int mPaid)
{
	card = c;
	int moneyOwed = mOwed;
	int moneyPaid = mPaid;
}
CommunityCards::~CommunityCards()
{

}
void CommunityCards::setCard(string c)
{
	card = c;
}
string CommunityCards::getCard()
{
	return card;
}
void CommunityCards::subMoneyOwed(int mOwed)
{
	moneyOwed = mOwed;
}
void CommunityCards::addMoneyPaid(int mPaid)
{
	moneyPaid = mPaid;
}
