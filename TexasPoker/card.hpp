/*
 * card.hpp
 *
 * 	Class card is used to simulate a single card in poker
 *
 *  Created on: Dec 7, 2010
 *      Author: jason
 */
#include <string>
#include "tools.hpp"

#pragma once

using namespace std;

enum Suit {							// different suit in poker:  ♣ ♦ ♥ ♠
	Diamond,Heart,Club,Spade
};

class Card {						// Card have two data members to indicate the numeric value and the suit of the card
private:
	Suit suit;
	int cardinalValue;

public:
	Card(Suit SuitInit, int CardInit):suit(SuitInit),cardinalValue(CardInit){	// initiate the default value
	}

	int getCardinal(); 							// Get cardinal value of card.
	Suit getSuit(); 							// Get suit of card.
	string nameOf();							// Get string representation of card.

	inline bool operator==(Card &other) {		// overload == operator to check if two cards are same
		return (this->getCardinal() == other.getCardinal() && this->getSuit() == other.getSuit());
	}
};
