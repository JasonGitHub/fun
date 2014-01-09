/*
 * board.cpp
 *
 *  Created on: Dec 7, 2010
 *      Author: jason
 */
#include "board.hpp"

void Board::flop(Poker &poker) { 					// start the game by placing a series of three cards (called the "flop") on the board
	CardPile flop;
	flop = poker.getFlop();
	add(flop);
}

void Board::turn(Poker &poker) {					// continue the game by enter the second deal called "turn"
	add(poker.getTurn());
}

void Board::river(Poker &poker) {					// the third deal, called "river"
	add(poker.getRiver());
}

void Board::burn(Poker &poker) {					// used to "burn cards" in the process of distributing cards
	poker.burnCard();
}

void Board::listShow() {							// show the cards on the table and the pot (money on the table)
	cout << "Current money on the board: " << pot << "." << endl;
	cout << "Current cards on the board: " << endl;
	show();
}

CardPile Board::getBoardCards() {					// return the cards on the board as a "CardPile"
	CardPile boardCards;
	for (it = cardpile.begin(); it != cardpile.end(); it++) {
		boardCards.add(*it);
	}
	return boardCards;
}

void Board::addMoney(int money) {					// add money to pot
	pot += money;
}

int Board::getPot() {								// return how much money is in the pot
	return pot;
}

void Board::removeMoney(int money) {				// remove money from the pot
	pot -= money;
}

void Board::removeMoney() {							// clear the money in the pot
	pot = 0;
}
