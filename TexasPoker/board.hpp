/*
 * board.hpp
 *
 *  Class Board is created to simulate the common area inside a game: which includes
 *  "Community Cards" shared by all players
 *  "The Pot" where players place their bets
 *
 *	This class is derived from class "CardPile" which simulate multiple cards.
 *
 *  Created on: Dec 7, 2010
 *      Author: jason
 */

#include "cardpile.hpp"
#include "poker.hpp"

#pragma once

class Board : public CardPile {	// derived from CardPile and have its own data member "pot" to record the money on the table
private:
	int pot;

public:
	Board():pot(0) {			// initiate the empty pot
	}

	void flop(Poker &poker);	// first deal, put 3 cards on the board
	void turn(Poker &poker);	// second deal, put 1 card on the board
	void river(Poker &poker);	// final deal, put 1 card on the board and ends
	void burn(Poker &poker);	// "Burn Card", discard one card in the process of distributing cards
	void listShow();			// show the cards on the table and the pot money
	CardPile getBoardCards();	// return the cards on the board
	void addMoney(int money);	// add money into the pot
	int getPot();				// return how much money is in the pot
	void removeMoney(int money);// remove a certain amount of money from the pot
	void removeMoney();			// clear all the money in the pot
};
