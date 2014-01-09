/*
 * poker.hpp
 *
 *  Created on: Dec 7, 2010
 *      Author: jason
 */
#include "card.hpp"
#include "cardpile.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

#pragma once

using namespace std;

class Poker : public CardPile {
private:
	void init(); // initialized each card of the poker
	void shuffle();	//random shuffle the poker
public:
	Poker() {
		init();
		shuffle();
	}

	void reset(); // reinitialized the pile of poker for the use of next round
	CardPile getFlop(); // return the three flop cards
	Card getTurn(); // return the turn card
	Card getRiver(); // return the river card
	Card burnCard(); // discard a card
	CardPile getHoleCard(); // return two hole cards
};
