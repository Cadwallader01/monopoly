#include "player.h"
#include <vector>
#include <iostream>
using namespace std;

//playerFunctions
player::player()
{
	position = 0;
	token = -1;
	name = "PLAYER";
	money = 1500;
	utilityCount = 0;
	railroadCount = 0;
	jailTime = 0;
}
player::player(int p, int t, string n, int m, int u, int rail, int jail)
{
	position = p;
	token = t;
	name = n;
	money = m;
	utilityCount = u;
	railroadCount = rail;
	jailTime = jail;
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
void player::setjailTime(int j)
{
	jailTime = j;
}
int player::getjailTime()
{
	return jailTime;
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
		players.push_back(player(playerPosition, playerToken, name, 1500, 0, 0, 0));
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
		//cout << players[i].getjailTime() << endl;
	}
}
