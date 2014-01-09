/*
 * card.cpp
 *
 *  Created on: Dec 7, 2010
 *      Author: jason
 */

#include "card.hpp"

int Card::getCardinal() { 		// Get cardinal value of card.
	return cardinalValue;
}
Suit Card::getSuit() { 			// Get suit of card.
	return suit;
}
string Card::nameOf() {			// Get string representation of card.
	string suit_s;
	string cardinalValue_s;

	switch (suit) {							// interpret the "enum" in to displayable characters
	case Diamond: suit_s = "♦"; break;
	case Heart: suit_s = "♥"; break;
	case Club: suit_s = "♣"; break;
	case Spade: suit_s = "♠"; break;
	}

	switch (cardinalValue) {				// interpret the "enum" value to cards. "Ace" have the highest value, "2" have the lowest
	case 1: cardinalValue_s = "2"; break;
	case 2: cardinalValue_s = "3"; break;
	case 3: cardinalValue_s = "4"; break;
	case 4: cardinalValue_s = "5"; break;
	case 5: cardinalValue_s = "6"; break;
	case 6: cardinalValue_s = "7"; break;
	case 7: cardinalValue_s = "8"; break;
	case 8: cardinalValue_s = "9"; break;
	case 9: cardinalValue_s = "10"; break;
	case 10: cardinalValue_s = "J"; break;
	case 11: cardinalValue_s = "Q"; break;
	case 12: cardinalValue_s = "K"; break;
	case 13: cardinalValue_s = "A"; break;
	}

	return cardinalValue_s+suit_s;
}
