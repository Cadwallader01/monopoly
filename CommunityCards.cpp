#include "CommunityCards.h"
#include "player.h"
#include "game.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

//prototypes
void pauseTime(int);
void displayPlayerBalance(int, vector<player>&);
int makeMove(int, int, vector<player>&, vector<property>&);

/***************************************************************************/
/***********************COMMUNITY CARDS STRUCT FUNCTIONS********************/
/***************************************************************************/
CommunityCards::CommunityCards()
{
	card = "NULL";
	moneyOwed = 0;
	moneyPaid = 0;
	playerPosition = 0;
}
CommunityCards::CommunityCards(string c, int mOwed, int mPaid, int p)
{
	card = c;
	moneyOwed = mOwed;
	moneyPaid = mPaid;
	playerPosition = p;
}
void CommunityCards::setCard(string c)
{
	card = c;
}
string CommunityCards::getCard()
{
	return card;
}
int CommunityCards::getMoneyOwed()
{
	return moneyOwed;
}
int CommunityCards::getMoneyPaid()
{
	return moneyPaid;
}
void CommunityCards::setPlayerPosition(int p)
{
	playerPosition = p;
}
int CommunityCards::getPlayerPosition()
{
	return playerPosition;
}

void pickCommunityChestCard(int currentPlayer, vector<player>& players, vector<CommunityCards>& communityCard, vector<property>& properties)
{
	int cardPick = 0;
	//cardPick = rand()%16;	//currently only 16 cards total
	cout << endl << "                        " << communityCard[cardPick].getCard() << endl << endl;
	pauseTime(3);
	cout << endl << endl;


	/********************PLAYER OWES MONEY*******************/
	if (communityCard[cardPick].getMoneyOwed() > 0 && cardPick != 6 && cardPick != 9)
	{
		players[currentPlayer].subMoney(communityCard[cardPick].getMoneyOwed());
		displayPlayerBalance(currentPlayer, players);
	}
	/*******PLAYER PAID MONEY (but not from ALL PLAYERS)*****/
	else if (communityCard[cardPick].getMoneyPaid() > 0 && cardPick != 0 && cardPick != 6 && cardPick != 9)
	{
		players[currentPlayer].addMoney(communityCard[cardPick].getMoneyPaid());
		displayPlayerBalance(currentPlayer, players);
	}
	/********PLAYER RECEIVES GET OUT OF JAIL FREE CARD*******/
	if (cardPick == 4)
	{
		cout << "You've collect a Get out of Jail Free Card! Keep to use later or for a future trade!" << endl;
		players[currentPlayer].setJailCard(true);
		cout << players[currentPlayer].getJailCard() << endl;
	}
	//if player gets paid from all players
	if (cardPick == 6)
	{
		//Grand Opera Night (Collect $50 from every player for opening night seats)
		for (int i = 0; i < players.size(); i++)
		{
			if (players[i].getName() != players[currentPlayer].getName())
			{
				cout << players[i].getName() << " is paying you $50" << endl;
				pauseTime(2);
				players[i].subMoney(50);
				players[currentPlayer].addMoney(50);
				displayPlayerBalance(currentPlayer, players);
				pauseTime(1);
			}
		}
	}
	else if (cardPick == 9)
	{
		//It is your birthday (Collect $10 from each player)
		for (int i = 0; i < players.size(); i++)
		{
			if (players[i].getName() != players[currentPlayer].getName())
			{
				cout << players[i].getName() << " is paying you $10" << endl;
				pauseTime(2);
				players[i].subMoney(10);
				players[currentPlayer].addMoney(10);
				displayPlayerBalance(currentPlayer, players);
				pauseTime(1);
			}
		}
	}

	//if player position changes -FIX THE FIRST IF STATEMENT
	if (cardPick == 0)
	{
		int positionMove = 0;	//used to determine how many spaces need to get to <-Go
		//add functionality for entire board
		/*
		//if lands on first Community Chest space
		if (players[currentPlayer].getPosition() == 2)
		{
			positionMove = 38;
			players[currentPlayer].setPosition(makeMove(positionMove, currentPlayer, players, properties));
		}//if lands on second Community Chest space
		else if (players[currentPlayer].getPosition() == 17)
		{
			positionMove = 23;
			players[currentPlayer].setPosition(makeMove(positionMove, currentPlayer, players, properties));
		}//if lands on third Community Chest space
		else if (players[currentPlayer].getPosition() == 33)
		{
			positionMove = 7;
			players[currentPlayer].setPosition(makeMove(positionMove, currentPlayer, players, properties));
		}
		*/

		positionMove = 11;	//to go to GO space
		players[currentPlayer].setPosition(makeMove(positionMove, currentPlayer, players, properties));
	}
	//else if player specifically has to go to jail move to [10] on board
	else if (communityCard[cardPick].getPlayerPosition() == 10)
	{
		players[currentPlayer].setPosition(communityCard[cardPick].getPlayerPosition());
		players[currentPlayer].setjailTime(true);
		cout << "You are now in jail." << endl;
	}
}
void makeCommunityCards(vector<CommunityCards>& communityCards)
{
	//CommunityCards(string name, int moneyOwed, int moneyPaid, int playerPosition)
	communityCards.push_back(CommunityCards("Advance to Go (Collect $200)", 0, 200, 0));
	communityCards.push_back(CommunityCards("Bank error in your favor (Collect $200)", 0, 200, -1));
	communityCards.push_back(CommunityCards("Doctor's fees (Pay $50)", 50, 0, -1));
	communityCards.push_back(CommunityCards("From sale of stock you get $50 (Collect $50)", 0, 50, -1));
	communityCards.push_back(CommunityCards("Get Out of Jail Free (Collect Get out of Jail Free Card)", 0, 0, -1));
	communityCards.push_back(CommunityCards("Go to Jail - Go directly to jail - Do not pass Go - Do not collect $200", 0, 0, 10));
	communityCards.push_back(CommunityCards("Grand Opera Night (Collect $50 from every player for opening night seats)", 0, 50, -1));
	communityCards.push_back(CommunityCards("Holiday Fund matures (Collect $100)", 0, 100, -1));
	communityCards.push_back(CommunityCards("Income tax refund (Collect $20)", 0, 20, -1));
	communityCards.push_back(CommunityCards("It is your birthday (Collect $10 from each player)", 0, 10, -1));
	communityCards.push_back(CommunityCards("Life insurance matures (Collect $100)", 0, 100, -1));
	communityCards.push_back(CommunityCards("Pay hospital fees (Pay $100)", 100, 0, -1));
	communityCards.push_back(CommunityCards("Pay school fees (Pay $150)", 150, 0, -1));
	communityCards.push_back(CommunityCards("Receive $25 consultancy fee (Collect $25)", 0, 25, -1));
	//communityCards.push_back(CommunityCards("You are assessed for street repairs (Pay $40 per house, $115 per hotel)", 0, 0, -1));
	communityCards.push_back(CommunityCards("You have won second prize in a beauty contest (Collect $10)", 0, 10, -1));
	communityCards.push_back(CommunityCards("You inherit $100 (Collect $100)", 0, 100, -1));
}
