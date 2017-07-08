#include "player.h"
#include "gameBoard.h"
#include <iostream>
#include <string>
using namespace std;

int main(){

	string name;	//to set player names
	

	cout << "Welcome to monopoly!" << endl;
	//create players
	player p1;
	player p2;
	//get player names
	cout << "What is name of player 1? ";
	cin >> name;
	p1.setName(name);
	cout << endl << "What is name of player 2? ";
	cin >> name;
	p2.setName(name);
	//display player information
	cout << endl;
	cout << p1.getName() << endl;
	cout << "Starting with: $" << p1.getMoney() << endl << endl;
	cout << p2.getName() << endl;
	cout << "Starting with: $" << p2.getMoney() << endl;

	/*jail
	connecticute avenue-120 rent 8
	vermont avenue-100 rent 6
	chance?
	oriental avenue-100 rent 6
	reading railroad-200 rent 25
	income tax-PAY200
	baltic avenue-60 rent 4
	Community chest
	mediterranean avenue-60 rent 2
	<-go-collect 200
	*/

	//THESE NEED TO BE REWRITTEN IN ORDER TO TRAVERSE THROUGH...
	//initialize square spaces sqaure(name, cost, rent, owned)
	gameBoard square1("Jail", 0, 0, false);
	gameBoard square2("Connecticute Avenue", 120, 8, false);
	gameBoard square3("Vermont Avenue", 100, 6, false);
	gameBoard square4("Chance", 0, 0, false);
	gameBoard square5("Oriental Avenue", 100, 6, false);
	gameBoard square6("Reading Railroad", 200, 25, false);
	gameBoard square7("INCOME TAX", 0, 200, false);
	gameBoard square8("Baltic Avenue", 60, 4, false);
	gameBoard square9("Community Chest", 0, 0, false);
	gameBoard square10("Mediterranean Avenue", 60, 2, false);
	gameBoard square11("<-Go!", 0, 0, false);
	


	//cout << "Lets play..." << endl;
	//get users to roll dice to see who will go first

	//insert while loop to continue to roll dice back and forth until a player loses

	system("pause");
	return 0;
}
