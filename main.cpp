#include "game.h"
#include "player.h"
#include "CommunityCards.h"
#include "chanceCards.h"
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
void propertyBuild(int, int, vector<player>&, vector<property>&);
void makeBoard(vector<property>&);
void displayBoard(vector<property>&);

//communityCard functions
void makeCommunityCards(vector<CommunityCards>&);
void pickCommunityChestCard(int, vector<player>&, vector<CommunityCards>&, vector<property>&);

//chanceCard functions
void makeChanceCards(vector<chanceCards>&);
void pickChanceCards(int, vector<player>&, vector<chanceCards>&);

int main(){

	int roll = 0;
	//WORKING ON: propertyBuild function
	//NEXT: -Test building houses
	//		-Add rest of board
	//		-Fix position changes for community chest cards...then test each card
	//		-Using community chest work on chance cards
	//WORKING ON: pickChanceCards function
	//			- adding if-then statements depending on which cards are picked and then making those cards available when
	//			  completed
	//NOTES: When community chest/chance cards are picked up make them unavailable to pick up again...since the vector
	//		 shrinks and some if statements depend on the position of the card vectors maybe I must add a new bool to the
	//		 constructor in order to see if card is available or not before picking up...will look into this later
	//NOTES: Add Community Chest Card that makes you fix houses/hotel
	//			-when added change the number of cards available in the pickCommunityChestCard function
	//NOTES: Add trade option for Get Out of Jail Free Card
	//NOTES: When player wants to build a house checkMonoply will check where they can build houses
	//			-work on functionality to build houses/hotels
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
			roll = diceRoll();
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
		userInput = " ";
		while (userInput != "n")
		{
			cout << "Would you like to do anything else? (Type 'n' for No, 'b' to build houses/hotels, 'p' to see your properties," << endl;
			cout << "or 'm' to see your monopolies (NOTE: Trading Unavailable) "<<endl; 
			cin >> userInput;
			cout << endl;
			//*************************************END TURN OPTIONS*********************************
			if (userInput == "b")
			{
				//***********************************BUILD HOUSES/HOTELS****************************
				propertyBuild(roll, currentPlayer, players, property);
				//cout << "building coming soon..." << endl;
			}
			else if(userInput == "p")
			{
				int playerToken = players[currentPlayer].getToken();
				unsigned int size = property.size();

				cout << "You own the following properties:" << endl;
				for (unsigned int i = 0; i<size; i++)
				{
					if (property[i].getOwnedBy() == playerToken)
					{
						cout << "[" << property[i].getMonopolyGroup() << "] " << property[i].getPropertyName() << endl;
					}
				}
			}
			else if(userInput == "m")
			{
				int playerToken = players[currentPlayer].getToken();
				unsigned int size = property.size();

				cout << "You own the following monopolies:" << endl;
				for (unsigned int i = 0; i<size; i++)
				{
					if (property[i].getMonopoly() == true && property[i].getOwnedBy() == playerToken)
					{
						cout << "[" << property[i].getMonopolyGroup() << "] " << property[i].getPropertyName() << endl;
					}
				}
			}
			cout << endl << endl;
		}//end while loop of END TURN OPTIONS
	}//end while loop of game

	cout << "The game has ended..." << endl;

	system("pause");
	return 0;
}
