#ifndef PLAYER_H
#define PLAYER_H
#include <string>
using namespace std;

struct player{
	
	int position;
	int token;
	string name;
	int money;
	int utilityCount;
	int railroadCount;
	int jailTime;

	player();
	player(int, int, string, int, int, int, int);
	void setPosition(int);
	int getPosition();

	void setToken(int);
	int getToken();

	void setName(string);
	string getName();

	void addMoney(int);
	void subMoney(int);
	int getMoney();		

	void setutilityCount(int);
	int getutilityCount();		

	void setrailroadCount(int);
	int getrailroadCount();

	void setjailTime(int);
	int getjailTime();
};
#endif
