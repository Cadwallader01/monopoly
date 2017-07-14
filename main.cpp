#include "player.h"
#include "gameBoard.h"
#include "CommunityCards.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>	//needed for randomized number
#include <chrono>	//system clock
#include <thread>	//sleep_for sleep_until
using namespace std;

//prototypes for functions
int diceRoll();
void makePurchase(int, int, vector<gameBoard>&, vector<player>&);
void makePlayer(vector<player>&);
void displayPlayer(vector<player>&);
void makeCommunityCards(vector<CommunityCards>&);
void displayCommunityCards(vector<CommunityCards>&);
void makeBoard(vector<gameBoard>&);
void displayBoard(vector<gameBoard>&);
void pauseTime();
int main(){

	//NOTES: WORK ON COMMUNITYCARDS HEADER/CPP and MAIN
	//			-work on jail cards?
	//			-work on cards that make you move places
	//			-work on cards that put you in jail
	//			-work on cards that give you money from other players
	//			-work on cards that make you pay players
	//			-work on cards that make you fix houses/hotels
	//NOTES: NEED TO ASSIGN A VALUE TO .SQUAREOWNED to correspond to the player that ownes it
	//NOTES: Before game starts ALLOW USERS TO ROLL DICE TO SEE WHO GOES FIRST

	srand(time(0)); //ensures randomized number by help of time
	//to get dice roll
	int playerRoll = 0;
	//varibles to change between players
	int currentPlayer = 1;
	int iteration = 0;
	//vectors for players and the board
	vector<player> players;
	vector<gameBoard> boardSquare;


	cout << "Welcome to monopoly!" << endl;
	//initialize players
	makePlayer(players);
	cout << "Current board:" << endl;
	//initialize and display board
	makeBoard(boardSquare);
	displayBoard(boardSquare);
	//display player information
	cout << endl;
	cout << players[0].getName() << endl;
	cout << "Starting with: $" << players[0].getMoney() << endl << endl;
	cout << players[1].getName() << endl;
	cout << "Starting with: $" << players[1].getMoney() << endl;

	//player one goes first
	cout << endl << endl << players[0].getName() << " you go first! Roll the dice!"<<endl;
	//loop to play the game
	while(players[currentPlayer].getMoney() > 0)
	{
		
		iteration++;
		if (iteration%2 != 0)
		{
			currentPlayer = 0;
		}
		//to switch between player 1 and 2
		if (iteration%2 == 0)

		{
			currentPlayer = 1;
		}
		else
		{
			currentPlayer = 0;
		}
		cout << "It's " << players[currentPlayer].getName() << "'s turn! Roll the dice!" << endl;
		//**********************************ROLLING THE DICE************************************
		int roll = diceRoll();
		cout << "You rolled a..." << roll << endl;
		//******************************MAKING/NOT MAKING A PURCHASE****************************
		cout << "You landed on: " << boardSquare[roll].getSquareName() << endl;
	//	if (boardSquare[roll].getSquareName() == "Community Chest")
	//		cout << "YOU ARE IN COMMUNITY CARDS+++++++++++++" << endl;


		//asks player if they would like to purchase square landed on if available
		makePurchase(roll, currentPlayer, boardSquare, players);
	}

	cout << "The game has ended..." << endl;

	system("pause");
	return 0;
}
void makePurchase(int square, int currentPlayer, vector<gameBoard>& boardSquare, vector<player>& players)
{
	string userInput;
	int cost = 0;
	if ((boardSquare[square].getSquareCost()) > 0)
	{
		cout << players[currentPlayer].getName() << " it's available to buy! Would you like to purchase for $" 
			 << boardSquare[square].getSquareCost() << "?" << endl;
		cout << "Type 'y' for Yes or 'n' for No " << endl;
		cin >> userInput;
		if (userInput == "y")
		{
			cost = boardSquare[square].getSquareCost();
			players[currentPlayer].subMoney(cost);
			cout << "Great! You now own " << boardSquare[square].getSquareName() << "!" << endl;
			cout << players[currentPlayer].getName() << " your new balance is $"
				 << players[currentPlayer].getMoney() << endl;
		}
		else if (userInput == "n")
		{
			cout << "Okay no purchase has been made!" << endl;
		}
	}
}
void pauseTime()
{
	std::chrono::seconds dura(5);
    std::this_thread::sleep_for(dura);
}
int diceRoll()
{
	//dice variables
	int dice1 = 0;
	int dice2 = 0;
	int totalDice = 0;
	//srand(time(0)); //ensures randomized number by help of time


	//**********************************ROLLING THE DICE************************************
	dice1 = rand()%6+1; //randomized number between 1-6
	dice2 = rand()%6+1; //randomized number between 1-6
	cout << "Dice one is: " << dice1 << endl;
	cout << "Dice two is: " << dice2 << endl <<endl;
	totalDice = dice1+dice2;

	return totalDice;
}
void makePlayer(vector<player>& players)
{
	int amountOfPlayers = 0;
	string name;
	cout << "How many players will be playing 1-2?: ";
	cin >> amountOfPlayers;

	for (int i = 0; i < amountOfPlayers; i++)
	{
		cout << "What is name of player " << i+1 << "? ";
		cin >> name;
		players.push_back(player(name, 1500, 0, 0, 0));
	}
}
void displayPlayer(vector<player>& players)
{
	unsigned int size = players.size();
	for (unsigned int i = 0; i < size; i++)
	{
		cout << players[i].getName() << endl;
		cout << players[i].getMoney() << endl;
		cout << players[i].getutilityCount() << endl;
		cout << players[i].getrailroadCount() << endl;
		cout << players[i].getjailTime() << endl;
	}
}
void makeCommunityCards(vector<CommunityCards>& communityCards)
{
	//initialize community cards
	//CommunityCards(string name, int moneyOwed, int moneyPaid)
	communityCards.push_back(CommunityCards("Advance to Go (Collect $200)", 0, 200));
	communityCards.push_back(CommunityCards("Bank error in your favor (Collect $200", 0, 200));
	communityCards.push_back(CommunityCards("Doctor's fees (Pay $50)", 50, 0));
	communityCards.push_back(CommunityCards("From sale of stock you get $50 (Collect $50)", 0, 50));
	//communityCards.push_back(CommunityCards("Get Out of Jail Free (Get out of Jail, Free)", 0, 0));
	//communityCards.push_back(CommunityCards("Go to Jail - Go directly to jail - Do not pass Go - Do not collect $200", 0, 0));
	//communityCards.push_back(CommunityCards("Grand Opera Night (Collect $50 from every player for opening night seats)", 0, 50));
	communityCards.push_back(CommunityCards("Holiday Fund matures (Collect $100)", 0, 100));
	communityCards.push_back(CommunityCards("Income tax refund (Collect $20)", 0, 20));
	//communityCards.push_back(CommunityCards("It is your birthday (Collect $10 from each player)", 0, 10));
	communityCards.push_back(CommunityCards("Life insurance matures (Collect $100)", 0, 100));
	communityCards.push_back(CommunityCards("Pay hospital fees (Pay $100)", 100, 0));
	communityCards.push_back(CommunityCards("Pay school fees (Pay $150)", 150, 0));
	communityCards.push_back(CommunityCards("Receive $25 consultancy fee (Collect $25)", 0, 25));
	//communityCards.push_back(CommunityCards("You are assessed for street repairs (Pay $40 per house, $115 per hotel)", 0, 0));
	communityCards.push_back(CommunityCards("You have won second prize in a beauty contest (Collect $10)", 0, 10));
	communityCards.push_back(CommunityCards("You inherit $100 (Collect $100)", 0, 100));
}
void displayCommunityCards(vector<CommunityCards>&);
void makeBoard(vector<gameBoard>& boardSquare){
	//initialize square spaces
	boardSquare.push_back(gameBoard("<-Go", 0, 0, false));
	boardSquare.push_back(gameBoard("Mediterranean Avenue", 60, 2, false));
	boardSquare.push_back(gameBoard("Community Chest", 0, 0, false));
	boardSquare.push_back(gameBoard("Baltic Avenue", 60, 4, false));
	boardSquare.push_back(gameBoard("INCOME TAX", 0, 200, false));
	boardSquare.push_back(gameBoard("Reading Railroad", 200, 25, false));
	boardSquare.push_back(gameBoard("Oriental Avenue", 100, 6, false));
	boardSquare.push_back(gameBoard("Chance?", 0, 0, false));
	boardSquare.push_back(gameBoard("Vermont Avenue", 100, 6, false));
	boardSquare.push_back(gameBoard("Connecticute Avenue", 120, 8, false));
	boardSquare.push_back(gameBoard("Jail", 0, 0, false));
	boardSquare.push_back(gameBoard("St. Charles Place", 140, 10, false));
	boardSquare.push_back(gameBoard("Electric Company", 150, 0, false));
}
void displayBoard(vector<gameBoard>& boardSquare){

	unsigned int size = boardSquare.size();
	for (unsigned int i = 0; i<size; i++)
	{
		cout << boardSquare[i].getSquareName() << endl;
		//The rest of the board is found below...
		/*cout << boardSquare[i].getSquareName() << endl;
		cout << boardSquare[i].getSquareCost() << endl;
		cout << boardSquare[i].getSquareRent() << endl;
		cout << boardSquare[i].getSquareOwned() << endl;
		*/
	}
}
