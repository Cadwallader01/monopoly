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

	void addMoney(int);
	void subMoney(int);
	int getMoney();		

	void setutilityCount(int);	//setter
	int getutilityCount();		//getter

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
