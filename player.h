#ifndef PLAYER_H_
#define PLAYER_H_
#include <string>
using namespace std;

class player
{
public:
	player();
	~player();
	void setName(string);
	string getName();

	void setMoney(int);	//setter
	int getMoney();		//getter

	void setutilityCount(int);
	int getutilityCount();

	void setrailroadCount(int);
	int getrailroadCount();

	void setjailTime(int);
	int getjailTime();

private:
	string name;
	int money;
	int utilityCount;
	int railroadCount;
	int jailTime;
};

#endif
