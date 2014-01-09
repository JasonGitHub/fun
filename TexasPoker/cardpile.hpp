/*
 * cardpile.hpp
 *
 * 	Class "CardPile" is used to simulate the abstract idea of "Several Cards", to encapsulate this is useful in this program because
 *  there are many circumstances in the game that requires to operate on several cards.
 *
 * 	the Board (common cards on the table) : derived class "Board"
 *  Player's Hole Cards : player's data memeber "HoleCards"
 *  the Poker Deck : derived class "Poker"
 *  and there are many other use of CardPile in different parts of this program
 *
 *  Created on: Dec 7, 2010
 *      Author: jason
 */

#include "card.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

#pragma once

using namespace std;

class CardPile {
protected:
	vector<Card> cardpile;	// internally stores cardpile in a vector
	vector<Card> :: iterator it; // the iterator

public:
	CardPile() {
	}
	void add(Card card); // add a card into pile
	void add(CardPile pile); // add a pile into pile
	void remove(Card card); // remove a card from the pile
	void removeAll(); // remove all cards from the pile
	Card pop(); // pop the card at the top
	Card getCard(int index); // return the card at position "index"
	int searchCard(Card card); // search for a card and return its index, if no found, will return -1
	unsigned int getNum(); // return the number of cards remained in the pile
	void sortCard(); // sort the cards to descending order, according to its "cardinalValue"
	void show(); // show  all card on console horizontally
	void showUnknown(); // show cards as unknown
	virtual void listShow(); // show all card on console as a list

	inline Card operator[](int index) {	// overload the indexing operator
		return getCard(index);
	}
};
