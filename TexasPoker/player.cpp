/*
 * player.cpp
 *
 *  Created on: Dec 7, 2010
 *      Author: jason
 */
#include "player.hpp"

int Player::counter = 1;	// start the counter from "1"

int Player::getId() {		// return the id of a player
	return id;
}

void Player::addHoleCards(CardPile pair) {	// give the two Hole cards to the players
	holecards.add(pair);
}

void Player::winMoney(int win) {	// give the money the player wins
	money+=win;
}

void Player::clearHand() {	// clear all cards a player have
	holecards.removeAll();
}

Status Player::getStatus() {	// get the status of a player
	return status;
}

void Player::clearStatus() {	// clear the status
	status = NORMAL;
}

void Player::showCards() {	// show the cards a player have on the console
	cout << "Cards of Player <" << id << ">: " << endl;
	holecards.show();
}

void Player::showMoney() {	// show how much money a player have
	cout << "Money of Player <" << id << ">: " << money << "." << endl;
}

void Player::showRole() {	// show the role of the player on the console
	string role_name;
	switch(role) {
	case SmallBlind: role_name = "SmallBlind"; break;
	case BigBlind: role_name = "BigBlind"; break;
	case Dealer: role_name = "Dealer"; break;
	case Ordinary: role_name = "Ordinary"; break;
	default:;
	}
	cout << "The role of Player <" << id << "> is " << role_name << "." << endl;
}

Role Player::getRole() {	// return the role of the player
	return role;
}

void Player::setRole(Role role) {	// set the role of a player
	this -> role = role;
}

void Player::clearRole(){	// clear the role of a player
	role = Ordinary;
}

CardPile Player::getHoleCards() {	// return the Hole Cards of a player
	return holecards;
}

void Player::sortHoleCards(){	// sort the hole cards to descending order by the card's numeric value
	holecards.sortCard();
}

int Player::action(Board &board, map<int,int> &bet_table, int minbet) {		// take action in the player's turn. The player "Fold" "Call" "Raise" or "All In" in different circumstances

	Action action;
	int new_minbet = minbet;
	int selection;
	cout << endl << "************************ Player <" << id << ">'s turn to play: ******************************" << endl;
		    cout << "**********************************************************************************" << endl;
	showCards();
	cout << "Player <" << id << "> Please select:" << endl
	     << "(Now you have $"<< money << " , at least $" << minbet << " is required for bet)" << endl;

	if (money > minbet) {													// pop out the available user selections
		cout << "0: Fold." << endl
			 << "1. Call." << endl
			 << "2. Raise." << endl;
		selection = 2;
	}
	else if (money <= minbet && money > 0) {
		cout << "0: Fold." << endl
			 << "1. All in." << endl;
		selection = 1;
	}
	else {
		cout << "Player <" << id << "> run out of money." << endl;
		fold();
		return minbet;
	}

	while (true) {															// get the user selection from keyboard
		int action_int = getInteger();
		if (action_int >= 0 && action_int <= selection) {
			action = Action(action_int); break;
		}
		cout << "Please select from the former choices." << endl;
	}

	if (action == Fold) fold();												// interpret user's selection
	else if (action == Call) new_minbet = call(board,bet_table,minbet);
	else if (action == Raise) new_minbet = raise(board,bet_table,minbet);
	else fatal ("Error in processing user choice.");

	return new_minbet;
}

int Player::call(Board &board, map<int,int> &bet_table, int minbet) {
	if (money <= minbet) {													// check if the player all in
		board.addMoney(money);
		bet_table[id] = money;
		cout << "Player <" << id << "> All in, and put $" << money << " in the pot." << endl;
		money = 0;
		status = ALLIN;
		return minbet;
	}
	else {
		money -= minbet;													// if not use standard call sequence
		board.addMoney(minbet);
		bet_table[id] = minbet;
		cout << "Player <" << id << "> calls and put $"<< minbet << " in the pot." << endl
			 << "Player <" << id << "> now have $"<< money << "." << endl;
	}
	return minbet;
}

int Player::raise(Board &board, map<int,int> &bet_table, int minbet) {		// the action "Raise"

	int new_minbet = minbet;

	cout << "Player <" << id << "> raise." << endl
	     << "How much do you want to raise?" << endl;

	while (true) {														// get how much money the player want to raise from keyboard and check for illegal input
		int raise = getInteger();

		if (raise >=1 && (raise+minbet) < money) {
			money -= (raise + minbet);
			board.addMoney(raise + minbet);
			bet_table[id] = raise + minbet;
			new_minbet = raise + minbet;
			cout << "Player <" << id << "> raise $" << raise << " and put $" << (raise+minbet) << " in the pot" << endl;
			break;
		}
		else if (raise >=1 && (raise+minbet) == money) {
			money = 0;
			board.addMoney(raise+minbet);
			bet_table[id] = raise + minbet;
			new_minbet = raise + minbet;
			cout << "Player <" << id << "> All in and put $" << (raise+minbet) << " in the pot" << endl;
			status = ALLIN;
			break;
		}
		else if ((raise+minbet) > money) {
			cout << "Don't be crazy! You don't have $" << (raise+minbet) << " !" << endl;
		}
		else if (raise < 1) {
			cout << "Are You Kidding Me? You can't raise less than $1!" << endl;
		}
	}

	cout << "Player <" << id << "> now have $"<< money << "." << endl;
	return new_minbet;
}

void Player::fold() {	// Player action "Fold"
	status = FOLD;
	cout << "Player <" << id << "> have fold." << endl;
}

void Player::blindBet(int bet, Board &board) { // This is used in the begining of a deal, the system will bet automatically for BigBlind and SmallBlind Players
	cout << endl << "************************ Player <" << id << ">'s turn to play: ******************************" << endl;
	        cout << "**********************************************************************************" << endl;

	if (money < bet) {
		fold();
		return;
	}
	money-=bet;
	board.addMoney(bet);

	cout << "<#SYSTEM INFO#> (Blind Player) System put $"<< bet << " in pot for Player <" << id << ">." << endl
	     << "Player <" << id << "> now have $"<< money << "." << endl;
	showCards();
}
