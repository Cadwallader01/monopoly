#include "game.h"
#include "player.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>	//needed for randomized number
#include <chrono>	//system clock
#include <thread>	//sleep_for sleep_until
using namespace std;

//PROTOTYPES
//player functions
void makePlayer(vector<player>&);
void displayPlayer(vector<player>&);
string findOwner(int, vector<player>&);
void checkJailStatus(int, vector<player>& players);
bool checkMonopoly(int, int, vector<player>&, vector<property>&);
void makePurchase(int, int, vector<property>&, vector<player>&);

//game functions
void pauseTime(int);
int diceRoll();
int makeMove(int, int, vector<player>&, vector<property>&);
void otherSpaces(int, int, vector<player>&, vector<property>&, vector<CommunityCards>&, vector<chanceCards>&);
void makeBoard(vector<property>&);
void displayBoard(vector<property>&);

//communityCard functions
void makeCommunityCards(vector<CommunityCards>&);
void pickCommunityChestCard(int, vector<player>&, vector<CommunityCards>&);

//chanceCard functions
void makeChanceCards(vector<chanceCards>&);
void pickChanceCards(int, vector<player>&, vector<chanceCards>&);

int main(){

	//WORKING ON: pickCommunityChestCard
	//			-work on cards that give you money from other players
	//			-work on cards that make you pay players
	//			-work on cards that make you fix houses/hotels

	//NOTES: When player wants to build a house checkMonoply will check where they can build houses
	//			-work on functionality to build houses/hotels
	//NOTES: Work on Chance Cards
	//NOTES: Before game starts ALLOW USERS TO ROLL DICE TO SEE WHO GOES FIRST
	//NOTES: Buying - make sure player has enough money to buy---otherwise can't afford property


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
	//display player information
	cout << endl;
	displayPlayer(players);
	pauseTime(3);
	cout << endl << endl << "Current Monopoly Board" << endl;
	//initialize and display board
	makeBoard(property);
	displayBoard(property);
	cout << endl;
	pauseTime(5);
	//initialize community cards
	makeCommunityCards(communityCard);
	//initialize chance cards
	makeChanceCards(chanceCard);

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
		//********************CHECK IF PLAYER IS IN JAIL BEFORE THEY CAN MOVE*******************
		if (players[currentPlayer].getjailTime() == false)
		{
			//**********************************ROLLING THE DICE************************************
			cout << "It's " << players[currentPlayer].getName() << "'s turn! Roll the dice!" << endl;
			pauseTime(5);	//pause for 5 seconds
			//**********************************ROLLING THE DICE************************************
			int roll = diceRoll();
			cout << "You rolled a " << roll << endl;
			pauseTime(5);	//pause for 5 seconds
			//sets player position-coming back around the board if necessary
			roll = makeMove(roll, currentPlayer, players, property);
			players[currentPlayer].setPosition(roll);
		
			//******************************MAKING/NOT MAKING A PURCHASE****************************
			cout << "You landed on: " << property[roll].getPropertyName() << endl;
			//check if player can purchase square or if square is owned
			makePurchase(roll, currentPlayer, property, players);
			//check if square is Go, Community Chest, or Chance and do necessary...
			otherSpaces(roll, currentPlayer, players, property, communityCard, chanceCard);
		}
		else if (players[currentPlayer].getjailTime() == true)
		{
			checkJailStatus(currentPlayer, players);
		}
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
