#include "player.h"
#include <string>
#include <iostream>

player::player()
{
	name = "player";
	money = 1500;
	utilityCount = 0;
	railroadCount = 0;
	jailTime = 0;
}
player::~player()
{
}
void player::setName(string n)
{
	name = n;
}
string player::getName()
{
	return name;
}
	void addMoney(int);
	void subMoney(int);
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
