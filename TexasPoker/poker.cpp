/*
 * poker.cpp
 *
 *  Created on: Dec 7, 2010
 *      Author: jason
 */
#include "poker.hpp"

void Poker::init() { // initialized each card of the poker
	for (int j = 0; j <= 3; j++) {
		for (int k = 1; k <= 13; k++) {
			Card card(Suit(j), k);
			cardpile.push_back(card);
		}
	}
}

void Poker::shuffle() { //random shuffle the poker
	random_shuffle(cardpile.begin(),cardpile.end());
}

void Poker::reset() { // reinitialized the pile of poker for the use of next round
	cardpile.clear();
	init();
}

CardPile Poker::getFlop() { // return the three flop cards
	CardPile flop;
	flop.add(pop());
	flop.add(pop());
	flop.add(pop());
	return flop;
}

Card Poker::getTurn() { // return the turn card
	return pop();
}

Card Poker::getRiver() { // return the river card
	return pop();
}

Card Poker::burnCard() { // discard a card
	return pop();
}

CardPile Poker::getHoleCard() { // return two hole cards
	CardPile holecard;
	holecard.add(pop());
	holecard.add(pop());
	return holecard;
}
