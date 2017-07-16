#include "player.h"
#include <string>
#include <iostream>

player::player()
{
	position = 0;
	token = 0;
	name = "player";
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
player::~player()
{
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
