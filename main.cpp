#include "game.h"
#include "player.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>	//needed for randomized number
#include <chrono>	//system clock
#include <thread>	//sleep_for sleep_until
using namespace std;

//prototypes for functions
void pauseTime();
int diceRoll();
//player functions
void makePurchase(int, int, vector<property>&, vector<player>&);
void makePlayer(vector<player>&);
void displayPlayer(vector<player>&);
//movement functions
int makeMove(int, int, vector<player>&, vector<property>&);
string findOwner(int, vector<player>&);
//communityCard functions
void makeCommunityCards(vector<CommunityCards>&);
void pickCommunityChestCard(int, vector<player>&, vector<CommunityCards>&);
void displayCommunityCards(vector<CommunityCards>&);
//chanceCard functions
void makeChanceCards(vector<chanceCards>&);
void pickChanceCards(int, vector<player>&, vector<chanceCards>&);
//board functions
void makeBoard(vector<property>&);
void makeCommunityCards(vector<CommunityCards>&);
bool checkMonopoly(int, int, vector<player>&, vector<property>&);
void otherSpaces(int, int, vector<player>&, vector<property>&, vector<CommunityCards>&, vector<chanceCards>&);
void displayBoard(vector<property>&);

int main(){

	//WORKING ON: building otherSpaces function

	//NOTES: When player wants to build a house checkMonoply will check where they can build houses
	//NOTES: Check if made a monopoly with last purchase or if user selects option to build
	//			-work on functionality to build houses/hotels
	//NOTES: Work on Community Cards
	//			-work on jail cards?
	//			-work on cards that make you move places
	//			-work on cards that put you in jail
	//			-work on cards that give you money from other players
	//			-work on cards that make you pay players
	//			-work on cards that make you fix houses/hotels
	//NOTES: Work on Chance Cards
	//NOTES: Before game starts ALLOW USERS TO ROLL DICE TO SEE WHO GOES FIRST
	//NOTES: Buying - make sure player has enough money to buy---otherwise can't afford property
	//NOTES: Change items to refer to "properties" vs squares/boardSquares?-doesn't seem valid for jail, community, chance


	string userInput;
	srand(time(0)); //ensures randomized number by help of time
	//to get dice roll
	int playerRoll = 0;
	//varibles to change between players
	int currentPlayer = 0;
	int iteration = 0;
	//vectors for players, property spaces, and community cards
	vector<player> players;
	vector<property> property;
	vector<CommunityCards> communityCard;
	vector<chanceCards> chanceCard;

	cout << "Welcome to monopoly!" << endl;
	//initialize players
	makePlayer(players);
	cout << endl << endl << "Current board:" << endl;
	//initialize and display board
	makeBoard(property);
	displayBoard(property);
	//initialize community cards
	makeCommunityCards(communityCard);
	//initialize chance cards
	makeChanceCards(chanceCard);

	//display player information
	cout << endl;
	displayPlayer(players);

	//loop to play the game
	while(players[currentPlayer].getMoney() > 0)
	{
		//if there is more than 1 player switch between them
		if (players.size() > 1)
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
		}

		cout << endl << endl << endl << "----------------------------------TURN----------------------------" << endl;
		cout << "It's " << players[currentPlayer].getName() << "'s turn! Roll the dice!" << endl;
		pauseTime();
		//**********************************ROLLING THE DICE************************************
		int roll = diceRoll();
		cout << "You rolled a..." << roll << endl;
		//sets player position-coming back around the board if necessary
		roll = makeMove(roll, currentPlayer, players, property);
		players[currentPlayer].setPosition(roll);
		
		//******************************MAKING/NOT MAKING A PURCHASE****************************
		cout << "You landed on: " << property[roll].getPropertyName() << endl;
		//check if player can purchase square or if square is owned
		makePurchase(roll, currentPlayer, property, players);
		//check if square is Go, Community Chest, or Chance and do necessary...
		otherSpaces(roll, currentPlayer, players, property, communityCard, chanceCard);
		//**************************************OTHER OPTIONS***********************************
		cout << "Would you like to do anything else? (Type 'b' for build or 'n' for No (NOTE: Trading Unavailable) "<<endl; 
		cin >> userInput;
		if (userInput == "b")
		{
			cout << "building coming soon..." << endl;
		}


	}

	cout << "The game has ended..." << endl;

	system("pause");
	return 0;
}
