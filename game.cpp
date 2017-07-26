#include "game.h"
#include "player.h"
#include <vector>
#include <iostream>
#include <ctime>	//needed for randomized number
#include <chrono>	//system clock
#include <thread>	//sleep_for sleep_until
using namespace std;

//prototypes
bool checkMonopoly(int, int, vector<player>&, vector<property>&);
string findOwner(int, vector<player>&);

/**************************PROPERTY STRUCT FUNCTIONS*************************/
property::property()
{
	monopoly = 0;
	squareName = "NULL";
	squareCost = 0;
	//int house;
	squareRent = 0;
	squareOwned = false;
}
property::property(int m, string n, int c, int r, bool o, int oB)
{
	monopoly = m;
	squareName = n;
	squareCost = c;
	squareRent = r;
	squareOwned = o;
	ownedBy = oB;
}
void property::setMonopoly(int m)
{
	monopoly = m;
}
int property::getMonopoly()
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
//void setHouse(int);
//int getHouse();
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

/***********************COMMUNITY CARDS STRUCT FUNCTIONS*********************/
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

/************************CHANCE CARDS STRUCT FUNCTIONS***********************/
chanceCards::chanceCards(){
	card = "NULL";
	moneyOwed = 0;
	moneyPaid = 0;
}
chanceCards::chanceCards(string c, int mOwed, int mPaid)
{
	card = c;
	moneyOwed = mOwed;
	moneyPaid = mPaid;
}
void chanceCards::setCard(string c)
{
	card = c;
}
string chanceCards::getCard()
{
	return card;
}
int chanceCards::getMoneyOwed()
{
	return moneyOwed;
}
int chanceCards::getMoneyPaid()
{
	return moneyPaid;
}


/*******************************OTHER FUNCTIONS*****************************/
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
//determine if property is available for purchase and finalize one if needed
void makePurchase(int space, int currentPlayer, vector<property>& properties, vector<player>& players)
{
	string owner = " ";
	string userInput;
	int cost = 0;
	bool monopolyMade = false;
	int monopolyTally = 0;
	unsigned int size = properties.size();
	int monopolyGroup = properties[space].getMonopoly();
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
					if (properties[i].getMonopoly() == monopolyGroup)
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
//used to currect the roll from going past current vector size and changes it to correct position
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
//initialize gameboard squares
void makeBoard(vector<property>& properties){
	//initialize square spaces
	//gameBoard(Monopoly, squareName, squareCost, squareRent, squareOwned, ownedBy)
	properties.push_back(property(-2, "<-Go", 0, 0, false, -2));
	properties.push_back(property(1, "Mediterranean Avenue", 60, 2, false, -1));
	properties.push_back(property(-2, "Community Chest", 0, 0, false, -2));
	properties.push_back(property(1, "Baltic Avenue", 60, 4, false, -1));
	properties.push_back(property(-2, "INCOME TAX", 0, 200, false, -2));
	properties.push_back(property(2, "Reading Railroad", 200, 25, false, -1));
	properties.push_back(property(3, "Oriental Avenue", 100, 6, false, -1));
	properties.push_back(property(-2, "Chance?", 0, 0, false, -2));
	properties.push_back(property(3, "Vermont Avenue", 100, 6, false, -1));
	properties.push_back(property(3, "Connecticute Avenue", 120, 8, false, -1));
	properties.push_back(property(-2, "Jail", 0, 0, false, -2));
	properties.push_back(property(4, "St. Charles Place", 140, 10, false, -1));
	properties.push_back(property(5, "Electric Company", 150, 0, false, -1));
}

//determine owner of square landed on
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
	int monopolyGroup = properties[square].getMonopoly();
	unsigned int size = properties.size();
	//collect how many squares make up that current monopolyGroup
	for (unsigned int i = 0; i<size; i++)
	{
		if (properties[i].getMonopoly() == monopolyGroup)
		{
			monopolyTally++;
		}
	}
	//Ex. monopolyTally = 3
	//make sure the player owns the same amount of squares in that monopolyGroup
	for (unsigned int i = 0; i<size; i++)
	{
		if (properties[i].getMonopoly() == monopolyGroup)
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
	}
	else if (monopolyTally > 0)
	{
		monopoly = false;
	}
	return monopoly;
}

void pickCommunityChestCard(int currentPlayer, vector<player>& players, vector<CommunityCards>& communityCard)
{
	//currentPlayer
	//players vector
	int cardPick = 0;
	cardPick = rand()%13;	//currently only 13 cards total
	cout << endl << "                        " << communityCard[cardPick].getCard() << endl << endl;
	//if player owes money
	if (communityCard[cardPick].getMoneyOwed() > 0)
	{
		players[currentPlayer].subMoney(communityCard[cardPick].getMoneyOwed());
		//display player's new balance
		cout << players[currentPlayer].getName() << " your new balance is $"
			 << players[currentPlayer].getMoney() << endl;
	}
	//if player gets paid money
	else if (communityCard[cardPick].getMoneyPaid() > 0)
	{
		players[currentPlayer].addMoney(communityCard[cardPick].getMoneyPaid());
		//display player's new balance
		cout << players[currentPlayer].getName() << " your new balance is $"
			 << players[currentPlayer].getMoney() << endl;
	}

	//if player position changes
	if (communityCard[cardPick].getPlayerPosition() == 0)
	{
		players[currentPlayer].setPosition(communityCard[cardPick].getPlayerPosition());
	}
	else if (communityCard[cardPick].getPlayerPosition() == 10)
	{
		players[currentPlayer].setPosition(communityCard[cardPick].getPlayerPosition());
		players[currentPlayer].setjailTime(1);
		cout << "You are in jail now :(" << endl;
	}
}
void pickChanceCards(int currentPlayer, vector<player>& players, vector<chanceCards>& chanceCard)
{
	//if (setplayerPosition = 10) then put player IN JAIL NOT VISITING

	//NEXT To-do: For collect money from each player cards run a loop to take money from each player


	//currentPlayer
	//players vector
	int cardPick = 0;
	cardPick = rand()%5;	//currently only 5 cards total
	cout <<  chanceCard[cardPick].getCard() << endl;
	//if player owes money
	if (chanceCard[cardPick].getMoneyOwed() > 0)
	{
		players[currentPlayer].subMoney(chanceCard[cardPick].getMoneyOwed());
	}
	//if player gets paid money
	else if (chanceCard[cardPick].getMoneyPaid() > 0)
	{
		players[currentPlayer].addMoney(chanceCard[cardPick].getMoneyPaid());
	}

	//display player's new balance
	cout << players[currentPlayer].getName() << " your new balance is $"
		 << players[currentPlayer].getMoney() << endl;
}
//calls other functions if space landed on is not a property
void otherSpaces(int space, int currentPlayer, vector<player>& players, vector<property>& properties, vector<CommunityCards>& communityCard, vector<chanceCards>& chanceCard)
{
	//space = current space on
	//currentPlayer = represents current player
	if (properties[space].getPropertyName() == "Community Chest")
	{
		pickCommunityChestCard(currentPlayer, players, communityCard);
	}
	else if (properties[space].getPropertyName() == "INCOME TAX")
	{
		players[currentPlayer].subMoney(200);
		//display player's new balance
		cout << players[currentPlayer].getName() << " your new balance is $"
			<< players[currentPlayer].getMoney() << endl;
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

//display current gameboard
void displayBoard(vector<property>& properties){

	unsigned int size = properties.size();
	for (unsigned int i = 0; i<size; i++)
	{
		cout << i+1 << ". ";
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
//initialize community cards
void makeCommunityCards(vector<CommunityCards>& communityCards)
{
	//CommunityCards(string name, int moneyOwed, int moneyPaid, playerPosition)
	communityCards.push_back(CommunityCards("Advance to Go (Collect $200)", 0, 200, 0));
	communityCards.push_back(CommunityCards("Bank error in your favor (Collect $200)", 0, 200, -1));
	communityCards.push_back(CommunityCards("Doctor's fees (Pay $50)", 50, 0, -1));
	communityCards.push_back(CommunityCards("From sale of stock you get $50 (Collect $50)", 0, 50, -1));
	//communityCards.push_back(CommunityCards("Get Out of Jail Free (Get out of Jail free)", 0, 0, -1));
	communityCards.push_back(CommunityCards("Go to Jail - Go directly to jail - Do not pass Go - Do not collect $200", 0, 0, 10));
	//communityCards.push_back(CommunityCards("Grand Opera Night (Collect $50 from every player for opening night seats)", 0, 50, -1));
	communityCards.push_back(CommunityCards("Holiday Fund matures (Collect $100)", 0, 100, -1));
	communityCards.push_back(CommunityCards("Income tax refund (Collect $20)", 0, 20, -1));
	//communityCards.push_back(CommunityCards("It is your birthday (Collect $10 from each player)", 0, 10, -1));
	communityCards.push_back(CommunityCards("Life insurance matures (Collect $100)", 0, 100, -1));
	communityCards.push_back(CommunityCards("Pay hospital fees (Pay $100)", 100, 0, -1));
	communityCards.push_back(CommunityCards("Pay school fees (Pay $150)", 150, 0, -1));
	communityCards.push_back(CommunityCards("Receive $25 consultancy fee (Collect $25)", 0, 25, -1));
	//communityCards.push_back(CommunityCards("You are assessed for street repairs (Pay $40 per house, $115 per hotel)", 0, 0, -1));
	communityCards.push_back(CommunityCards("You have won second prize in a beauty contest (Collect $10)", 0, 10, -1));
	communityCards.push_back(CommunityCards("You inherit $100 (Collect $100)", 0, 100, -1));
}
void makeChanceCards(vector<chanceCards>& ChanceCards)
{
	//CommunityCards(string name, int moneyOwed, int moneyPaid)
	ChanceCards.push_back(chanceCards("Advance to Go (Collect $200)", 0, 200));
	//ChanceCards.push_back(chanceCards("Advance to Illinoise Ave. (If you pass Go, collect $200)", 0, 0));
	//ChanceCards.push_back(chanceCards("Advance to St. Charles Place (If you pass Go, collect $200)", 0, 0));
	//ChanceCards.push_back(chanceCards("Advance to nearest Utility (If unowned, you may buy it from the Bank. If owned, throw dice and pay owner a total ten times the amount thrown)", 0, 0));
	//ChanceCards.push_back(chanceCards("Advance to the nearest Railroad (If unowned, you may buy it from the Bank. If owned, pay owner twice the rental he/she is owed)", 0, 0));
	//ChanceCards.push_back(chanceCards("Advance to the nearest Railroad (If unowned, you may buy it from the Bank. If owned, pay owner twice the rental he/she is owed)", 0, 0));
	ChanceCards.push_back(chanceCards("Bank pays you dividend of $50 (Collect $50)", 0, 50));
	//ChanceCards.push_back(chanceCards("Get out of Jail Free (Get out of Jail free)", 0, 0));
	//ChanceCards.push_back(chanceCards("Go Back 3 Spaces", 0, 0));
	//ChanceCards.push_back(chanceCards("Go to Jail - Go directly to jail - Do not pass Go - Do not collect $200", 0, 0));
	//ChanceCards.push_back(chanceCards("Make general repairs on all your property (Pay $25 per house, $100 per hotel)", 0, 200));
	ChanceCards.push_back(chanceCards("Pay poor tax of $15 (Pay $15)", 15, 0));
	//ChanceCards.push_back(chanceCards("Take a trip to Reading Railroad (Take a ride on the Reading - If you pass Go, collect $200)", 0, 0));
	//ChanceCards.push_back(chanceCards("Take a walk on the Boardwalk (Advance to Boardwalk - If you pass Go, collect $200)", 0, 0));
	//ChanceCards.push_back(chanceCards("You have been elected Chairman of the Board (Pay each player $50)", 0, 0));
	ChanceCards.push_back(chanceCards("Your building and loan matures (Collect $150)", 0, 150));
	ChanceCards.push_back(chanceCards("You have won a crossword competition (Collect $100)", 0, 100));
}
