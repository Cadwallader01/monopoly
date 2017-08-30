#include "player.h"
#include "game.h"
#include <vector>
#include <iostream>
using namespace std;
//prototypes
bool checkMonopoly(int, int, vector<player>&, vector<property>&);
string findOwner(int, vector<player>&);

//playerFunctions
player::player()
{
	position = 0;
	token = -1;
	name = "PLAYER";
	money = 1500;
	utilityCount = 0;
	railroadCount = 0;
	jailBail = 3;	//starts at 3 and works it's way down to 0
	jailTime = 0;
	jailCard = 0;
}
player::player(int p, int t, string n, int m, int u, int rail, int jB, bool jT, bool jC)
{
	position = p;
	token = t;
	name = n;
	money = m;
	utilityCount = u;
	railroadCount = rail;
	jailBail = jB;
	jailTime = jT;
	jailCard = jC;
}
void player::setPosition(int p)
{

	position = p;
}
int player::getPosition()
{
	return position;
}
void player::setToken(int t)
{
	token = t;
}
int player::getToken()
{
	return token;
}
void player::setName(string n)
{
	name = n;
}
string player::getName()
{
	return name;
}
void player::addMoney(int m)
{
	money += m;
}
void player::subMoney(int m)
{
	money -= m;
}
int player::getMoney()
{
	return money;
}
void player::setutilityCount(int u)
{
	utilityCount = u;
}
int player::getutilityCount()
{
	return utilityCount;
}
void player::setrailroadCount(int r)
{
	railroadCount = r;
}
int player::getrailroadCount()
{
	return railroadCount;
}
void player::setJailBail(int j)
{
	jailBail = j;
}
int player::getJailBail()
{
	return jailBail;
}
void player::setjailTime(bool j)
{
	jailTime = j;
}
bool player::getjailTime()
{
	return jailTime;
}
void player::setJailCard(bool j)
{
	jailCard = j;
}
bool player::getJailCard()
{
	return jailCard;
}

//function to make a player
void makePlayer(vector<player>& players)
{
	int playerPosition = 0;
	int playerToken = 0;
	int amountOfPlayers = 0;
	string name;
	cout << "How many players will be playing 1-2?: ";
	cin >> amountOfPlayers;
	for (int i = 0; i < amountOfPlayers; i++)
	{
		cout << "What is name of player " << i+1 << "? ";
		cin >> name;
		//player(playerPosition, playerToken, playerName, playerMoney, utilityCount, railroadCount, jailBail, jailTime, jailCard)
		players.push_back(player(playerPosition, playerToken, name, 1500, 0, 0, 3, false, false));
		playerToken++;
	}
}
//display players
void displayPlayer(vector<player>& players)
{
	unsigned int size = players.size();
	for (unsigned int i = 0; i < size; i++)
	{
		//cout << players[i].getPosition() << endl;
		//cout << players[i].getToken() << endl;
		cout << players[i].getName() << endl;
		cout << "Starting with: $" << players[0].getMoney() << endl << endl;
		//cout << players[i].getMoney() << endl;
		//cout << players[i].getutilityCount() << endl;
		//cout << players[i].getrailroadCount() << endl;
		//cout << players[i].getJailBail() << endl;
		//cout << players[i].getjailTime() << endl;
	}
}
//determine who is owner of space landed on
string findOwner(int playerToken, vector<player>& players)
{
	unsigned int size = players.size();
	int foundPlayer = 0;
	for (unsigned int i = 0; foundPlayer == 0; i++)
	{
		players[i].getToken();
		if (players[i].getToken() == playerToken)
		{
			foundPlayer = 1;
			return players[i].getName();
		}
	}
}
//check if player has a monopoly
bool checkMonopoly(int square, int currentPlayer, vector<player>& players, vector<property>& properties)
{
	bool monopoly = false;
	int monopolyTally = 0;
	int playerToken = players[currentPlayer].getToken();
	int monopolyGroup = properties[square].getMonopolyGroup();
	unsigned int size = properties.size();
	//collect how many squares make up that current monopolyGroup
	for (unsigned int i = 0; i<size; i++)
	{
		if (properties[i].getMonopolyGroup() == monopolyGroup)
		{
			monopolyTally++;
		}
	}
	//Ex. monopolyTally = 3
	//make sure the player owns the same amount of squares in that monopolyGroup
	for (unsigned int i = 0; i<size; i++)
	{
		if (properties[i].getMonopolyGroup() == monopolyGroup)
		{
			//if player owns that square then monopolyTally--
			if (players[currentPlayer].getToken() == properties[i].getOwnedBy())
			{
				monopolyTally--;
			}
		}
	}
	//if monopolyTally == 0 then there is a monopoly else there isn't
	if (monopolyTally == 0)
	{
		monopoly = true;
		//turn monopoly variable of property to true if it is part of a monopoly
		for (unsigned int i = 0; i<size; i++)
		{
			if (properties[i].getMonopolyGroup() == monopolyGroup)
			{
				properties[i].setMonopoly(true);
			}
		}
	}
	else if (monopolyTally > 0)
	{
		monopoly = false;
	}
	return monopoly;
}
//determine if property is available for purchase and finalize one if needed
void makePurchase(int space, int currentPlayer, vector<property>& properties, vector<player>& players)
{
	string owner = " ";
	string userInput;
	int cost = 0;
	bool monopolyMade = false;
	int monopolyTally = 0;
	unsigned int size = properties.size();
	int monopolyGroup = properties[space].getMonopolyGroup();
	int playerToken = -1;
	//if square is not owned ask player if they'd like to make a purchase
	if (properties[space].getOwnedBy() == -1)
	{
		cout << players[currentPlayer].getName() << " it's available to buy! Would you like to purchase for $" 
			<< properties[space].getPropertyCost() << "?" << endl;
		cout << "Type 'y' for Yes or 'n' for No " << endl;
		cin >> userInput;
		if (userInput == "y")
		{
			cost = properties[space].getPropertyCost();
			players[currentPlayer].subMoney(cost);
			playerToken = players[currentPlayer].getToken();
			properties[space].setOwnedBy(playerToken);
			cout << "Great! You now own " << properties[space].getPropertyName() << "!" << endl;
			//check if player just made a monoply with purchase
			monopolyMade = checkMonopoly(space, currentPlayer, players, properties);
				//tell player that current purchase made a monopoly with these squares...
			if (monopolyMade == true)
			{
				cout << "You own a monopoly! with these squares: " <<endl;
				for (unsigned int i = 0; i<size; i++)
				{
					if (properties[i].getMonopolyGroup() == monopolyGroup)
					{
						cout << properties[i].getPropertyName() << endl;
					}
				}
			}
			//display player's new balance
			cout << players[currentPlayer].getName() << " your new balance is $"
				 << players[currentPlayer].getMoney() << endl;
		}
		else if (userInput == "n")
		{
			cout << "Okay no purchase has been made!" << endl;
		}
	}
	//if square is owned let player know who already owns it
	else if(properties[space].getOwnedBy() > -1)
	{
		playerToken = properties[space].getOwnedBy();
		owner = findOwner(playerToken, players);
		if (players[currentPlayer].getName() == owner)
		{
			cout << "You already own this!" << endl;
		}
		else
		{
			cout << "Sorry the square is already owned by " << owner << endl;
		}
	}
}
