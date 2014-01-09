/*
 * player.hpp
 *
 *	Class Player is used to simulate a human player in Texas Hold'em
 *
 *  Created on: Dec 7, 2010
 *      Author: jason
 */
#include "cardpile.hpp"
#include "board.hpp"
#include "tools.hpp"
#include <map>

#pragma once

const int default_start_money = 500;

using namespace std;

enum Role { // In each round, players have different roles, the first and second players left of the dealer are called "small blind" and "big blind"
	Dealer,SmallBlind,BigBlind,Ordinary
};

enum Action { // The action a player can choose in his/her turn
	Fold,Call,Raise
};

enum Status {	// The status of a player, record if a player AllIn or someone fold
	NORMAL,ALLIN,FOLD
};

class Player {
protected:
	static int counter; // internal counter used to generate id
	int id; // each player is identified by a unique id generated using a internal counter
	int money;
	Status status; // to determine a player have fold or AllIn
	Role role;	// the role of a player, Dealer, BigBlind, SmallBlind or Ordinary
	CardPile holecards; // cards in a player's hand, which are called "hole cards"

public:
	Player():id(counter),status(NORMAL),role(Ordinary){ // initiate the default value of a player
		while(true) {
			cout << "Please set the start money for Player <" << id << "> :";	// the "manual mode" constructor will let the user decide how much money each player have
			money = getInteger();
			if (money >= 10 && money <= 10000) break;
			else if (money < 10) cout << "The minimum to enter this table is $10, thanks." << endl;
			else cout << "The maximum for this table is $10000, thanks." << endl;
		}
		counter++;
	}

	Player(bool autoset):id(counter),money(default_start_money),status(NORMAL),role(Ordinary){ // the "automatic mode" constructor which will set start money of each player automatically
			counter++;
	}

	int getId(); // return the id of the player
	void addHoleCards(CardPile pair); // give the first two cards to the player
	void winMoney(int win); // win money
	void clearHand(); // remove all the cards of a player
	Status getStatus(); // get the status of a player
	void clearStatus(); // clear the status of a player
	void showCards(); // display all cards the player have
	void showMoney(); // display the money the player have
	void showRole(); // display the role of the player
	Role getRole(); // return the role of the player
	void setRole(Role role); // set the role of a player in each round
	void clearRole(); // clear the role of the player to Ordinary
	CardPile getHoleCards(); // return the player's hole cards
	void sortHoleCards(); // sort the HoleCards by numeric value

	// player actions in the game
	virtual int action(Board &board, map<int,int> &bet_table, int minbet); // simulates the player's turn, player can choose from "Call" "Raise" "Fold"
	virtual int call(Board &board, map<int,int> &bet_table, int minbet);
	virtual int raise(Board &board, map<int,int> &bet_table, int minbet);
	virtual void fold();
	virtual void blindBet(int bet, Board &board); // system bet for "Blind" players
};

