#include "game.h"
#include "player.h"
#include "CommunityCards.h"
#include "chanceCards.h"
#include <vector>
#include <iostream>
#include <ctime>	//needed for randomized number
#include <chrono>	//system clock
#include <thread>	//sleep_for sleep_until
using namespace std;

//prototypes
bool checkMonopoly(int, int, vector<player>&, vector<property>&);
string findOwner(int, vector<player>&);
void makePlayer(vector<player>&);
void displayPlayer(vector<player>&);
void makePurchase(int, int, vector<property>&, vector<player>&);
void pickCommunityChestCard(int, vector<player>&, vector<CommunityCards>&, vector<property>&);
void pickChanceCards(int, vector<player>&, vector<chanceCards>&);
/***************************************************************************/
/**************************PROPERTY STRUCT FUNCTIONS************************/
/***************************************************************************/
property::property()
{
	monopolyGroup = 0;
	squareName = "NULL";
	squareCost = 0;
	house;
	hotel;
	squareRent = 0;
	squareOwned = false;
}
property::property(int mG, bool m, string n, int hs, int ht, int c, int r, bool o, int oB)
{
	monopolyGroup = mG;
	monopoly = m;
	squareName = n;
	squareCost = c;
	house = hs;
	hotel = ht;
	squareRent = r;
	squareOwned = o;
	ownedBy = oB;
}
void property::setMonopolyGroup(int m)
{
	monopolyGroup = m;
}
int property::getMonopolyGroup()
{
	return monopolyGroup;
}
void property::setMonopoly(bool m)
{
	monopoly = m;
}
bool property::getMonopoly()
{
	return monopoly;
}
void property::setPropertyName(string s)
{
	squareName = s;
}
string property::getPropertyName()
{
	return squareName;
}
void property::setHouse(int hs)
{
	house = hs;
}
int property::getHouse()
{
	return house;
}
void property::setHotel(int ht)
{
	hotel = ht;
}
int property::getHotel()
{
	return hotel;
}
void property::setPropertyCost(int c)
{
	squareCost = c;
}
int property::getPropertyCost()
{
	return squareCost;
}
void property::setPropertyRent(int r)
{
	squareRent = r;
}
int property::getPropertyRent()
{
	return squareRent;
}
void property::setPropertyOwned(bool o)
{
	squareOwned = o;
}
bool property::getPropertyOwned()
{
	return squareOwned;
}
void property::setOwnedBy(int oB)
{
	ownedBy = oB;
}
int property::getOwnedBy()
{
	return ownedBy;
}

/***************************************************************************/
/********************************GAME FUNCTIONS*****************************/
/***************************************************************************/
//pause the game by seconds
void pauseTime(int time)
{
	std::chrono::seconds dura(time);
    std::this_thread::sleep_for(dura);
}
//rolling the dice
int diceRoll()
{
	//dice variables
	int dice1 = 0;
	int dice2 = 0;
	int totalDice = 0;
	//srand(time(0)); //ensures randomized number by help of time

	dice1 = rand()%6+1; //randomized number between 1-6
	dice2 = rand()%6+1; //randomized number between 1-6
	cout << "Dice one is: " << dice1 << endl;
	cout << "Dice two is: " << dice2 <<endl;
	totalDice = dice1+dice2;	//commented out for troubleshooting
	//totalDice = 2;

	return totalDice;
}
void displayPlayerBalance(int currentPlayer, vector<player>& players)
{
	//display player's new balance
	cout << players[currentPlayer].getName() << " your new balance is $" << players[currentPlayer].getMoney() << endl;
}
//used to correct the roll from going past current vector size and changes it to correct position
int makeMove(int roll, int currentPlayer, vector<player>& players, vector<property>& property)
{
	cout << "                        [" << players[currentPlayer].getName() << "'s Move]" << endl;
	int validPosition = players[currentPlayer].getPosition();
	//if player's roll goes past the current vector it will change to a valid move
	for (int i = 0; i<roll; i++)
	{
		pauseTime(1);
		if (validPosition == 12)
		{
			validPosition = -1;
		}
		validPosition++;
		//display player's move
		cout << "                   " << property[validPosition].getPropertyName() << endl;
		if (property[validPosition].getPropertyName() == "<-Go")
		{
			cout << endl;
			cout << "                   (Collect $200!)" << endl;
			players[currentPlayer].addMoney(200);
			//display player's new balance
			cout << "                   " << players[currentPlayer].getName() << " your new balance is $"
				 << players[currentPlayer].getMoney() << endl << endl;
			pauseTime(4);
		}

	}
	return validPosition;
}
//calls other functions if space landed on is not a property
void otherSpaces(int space, int currentPlayer, vector<player>& players, vector<property>& properties, vector<CommunityCards>& communityCard, vector<chanceCards>& chanceCard)
{
	//if space landed on is NOT a property or is a special type corresponding actions are taken
	if (properties[space].getPropertyName() == "Community Chest")
	{
		pickCommunityChestCard(currentPlayer, players, communityCard, properties);
	}
	else if (properties[space].getPropertyName() == "INCOME TAX")
	{
		players[currentPlayer].subMoney(200);
		//display player's new balance
		displayPlayerBalance(currentPlayer, players);
	}
	else if (properties[space].getPropertyName() == "Reading Railroad")
	{
		cout << "This is a railroad space..." << endl;
	}
	else if (properties[space].getPropertyName() == "Chance?")
	{
		pickChanceCards(currentPlayer, players, chanceCard);
	}
	else if (properties[space].getPropertyName() == "Jail")
	{
		cout << "This is Jail..." << endl;
	}
	else if (properties[space].getPropertyName() == "Electric Company")
	{
		cout << "This is a utitlity space..." << endl;
	}
}
//initialize gameboard squares
void makeBoard(vector<property>& properties){
	//gameBoard(Monopoly, squareName, house, hotelsquareCost, squareRent, squareOwned, ownedBy)
	properties.push_back(property(-2, false, "<-Go", 0, 0, 0, 0, false, -2));
	properties.push_back(property(1, false, "Mediterranean Avenue", 0, 0, 60, 2, false, -1));
	properties.push_back(property(-2, false, "Community Chest", 0, 0, 0, 0, false, -2));
	properties.push_back(property(1, false, "Baltic Avenue", 0, 0, 60, 4, false, -1));
	properties.push_back(property(-2, false, "INCOME TAX", 0, 0, 0, 200, false, -2));
	properties.push_back(property(2, false, "Reading Railroad", 0, 0, 200, 25, false, -1));
	properties.push_back(property(3, false, "Oriental Avenue", 0, 0, 100, 6, false, -1));
	properties.push_back(property(-2, false, "Chance?", 0, 0, 0, 0, false, -2));
	properties.push_back(property(3, false, "Vermont Avenue", 0, 0, 100, 6, false, -1));
	properties.push_back(property(3, false, "Connecticute Avenue", 0, 0, 120, 8, false, -1));
	properties.push_back(property(-2, false, "Jail", 0, 0, 0, 0, false, -2));
	properties.push_back(property(4, false, "St. Charles Place", 0, 0, 140, 10, false, -1));
	properties.push_back(property(5, false, "Electric Company", 0, 0, 150, 0, false, -1));
}
//display current gameboard
void displayBoard(vector<property>& properties){

	unsigned int size = properties.size();
	for (unsigned int i = 0; i<size; i++)
	{
		cout << i+1 << ". ";
		//cout << properties[i].getMonopolyGroup() << endl;
		//cout << properties[i].getMonopoly() << endl;
		cout << properties[i].getPropertyName() << endl;
		//The rest of the board is found below...
		/*cout << properties[i].getSquareName() << endl;
		cout << properties[i].getPropertyCost() << endl;
		cout << properties[i].getPropertyRent() << endl;
		cout << properties[i].getPropertyOwned() << endl;
		cout << properties[i].getOwnedBy() << endl;
		*/
	}
}

/***************************************************************************/
/******************************IN JAIL FUNCTIONS****************************/
/***************************************************************************/
//if player is in jail function asks them if they'd like to roll doubles or pay to get out-player has 3 tries total
void checkJailStatus(int currentPlayer, vector<player>& players)
{
	int jailBail = players[currentPlayer].getJailBail();
	int dice = 0;
	string userInput = " ";

	//use jailBail to count to 3...if player has rolled for doubles 3 times then they are forced to pay to get out
	//GIVE option to roll to get out of jail OR pay to just get out
	if (players[currentPlayer].getjailTime() == true && players[currentPlayer].getJailBail() > 0)
	{
		//display different message options depending if player has a Get Out of Jail Free Card or not
		if (players[currentPlayer].getJailCard() == false)
		{
			cout << "You are currently in jail. You may pay a fine of $50 or try to roll for doubles to get out." << endl;
			cout << "You have " << players[currentPlayer].getJailBail() << " tries left before you have to pay fine to get out." << endl;
			cout << "Type 'p' to pay $50 fine or 'r' to try to roll doubles!" << endl;
		}
		else if (players[currentPlayer].getJailCard() == true)
		{
			cout << "You are currently in jail. You may pay a fine of $50, try to roll for doubles, or use your Get"
				 << " Out of Jail Free Card to get out." << endl;
			cout << "You have " << players[currentPlayer].getJailBail() << " tries left before you have to pay fine to get out." << endl;
			cout << "Type 'p' to pay $50 fine, 'r' to try to roll doubles, or 'g' to use your Get Out of Jail Free Card" << endl;
		}
		cin >> userInput;
		if (userInput == "p")
		{
			players[currentPlayer].setJailBail(3);
			players[currentPlayer].setjailTime(false);
			players[currentPlayer].subMoney(50);
			displayPlayerBalance(currentPlayer, players);
		}
		else if (userInput == "r")
		{
			players[currentPlayer].setJailBail(jailBail-1);
			dice = diceRoll();
			if (dice % 2 == 0)
			{
				cout << "You rolled doubles! You are now out of jail and can move on your next turn!" << endl;
				players[currentPlayer].setjailTime(false);
			}
			else if ( dice % 2 != 0)
			{
				cout << "You did not roll doubles and are still in jail." << endl;
				players[currentPlayer].setjailTime(true);
			}
		}
		if (userInput == "g")
		{
			cout << "You've used your Get Out of Jail Free Card! You will be able to make a move on your next turn." << endl;
			players[currentPlayer].setJailBail(3);
			players[currentPlayer].setjailTime(false);
			players[currentPlayer].setJailCard(false);
		}
	}
	else if (players[currentPlayer].getjailTime() == true && players[currentPlayer].getJailBail() == 0)
	{
		cout << "You are currently in jail but have " << players[currentPlayer].getJailBail() << " tries left to roll doubles!" << endl;
		cout << "You must pay $50 to get out of jail." << endl;
		players[currentPlayer].setJailBail(3);
		players[currentPlayer].setjailTime(false);
		players[currentPlayer].subMoney(50);
		displayPlayerBalance(currentPlayer, players);
	}
	else
	{
		players[currentPlayer].setJailBail(3);
	}
}
//player has selected to build
void propertyBuild(int space, int currentPlayer, vector<player>& players, vector<property>& properties)
{
	
	int playerToken = players[currentPlayer].getToken();
	unsigned int size = properties.size();
	int userInput = 0;
	bool buildingAllowed = false;
	cout << "You can build on these properties: " << endl;
	for (unsigned int i = 0; i<size; i++)
	{
		if (properties[i].getOwnedBy() == playerToken && properties[i].getMonopoly() == true)
		{
			cout << "[" << properties[i].getMonopolyGroup() << "] " << properties[i].getPropertyName() << endl;
		}
	}
	//allow player to pick a property based off of the monopolyGroup
	cout << endl << endl;
	cout << "Type the number found in any of the above monopolies to pick that group of properties to build on." << endl;
	cout << "Example. If the number by your property looks like this [1] then type 1. ";
	cin >> userInput;
	//check userInput was correct...
	while (buildingAllowed != true)
	{
		for (unsigned int i = 0; i<size; i++)
		{
			//check if user picked a correct group of properties to build on and display properties
			if (properties[i].getOwnedBy() == playerToken && properties[i].getMonopoly() == true
				&& properties[i].getMonopolyGroup() == userInput)
			{
				buildingAllowed = true;
				cout << "buildingAllowed == true" << endl;
				cout << "[" << properties[i].getMonopolyGroup() << "] " << properties[i].getPropertyName() << endl;
			}
		}
		//if user did not type correct MonopolyGroup value ask them to type again
		if (buildingAllowed == false)
		{
			cout << "Sorry, that was an invalid entry. Please type out a number corresponding to the group of properties "
				 << "that you would like to build on: " << endl;
			cin >> userInput;
		}
	}
	/*build a house on the property*/
}
