/*
 * cardpile.cpp
 *
 *  Created on: Dec 7, 2010
 *      Author: jason
 */
#include "cardpile.hpp"

bool compFunction(Card a, Card b) {								// Compare function for <algrorithm> sort, will compare the numeric value of two cards
	return (a.getCardinal() > b.getCardinal());
}

void CardPile::add(Card card) {									// add cards
	cardpile.push_back(card);
}
void CardPile::add(CardPile pile) {								// add multiple cards
	for (unsigned int i = 0; i < pile.getNum(); i++){
	cardpile.push_back(pile.getCard(i));
	}
}
void CardPile::remove(Card card) {								// remove a specific card from a card
	for (it = cardpile.begin(); it != cardpile.end(); it++) {
		if (*it == card)
			cardpile.erase(it);
	}
}

void CardPile::removeAll() {									// remove all the cards from the card pile
	cardpile.clear();
}

Card CardPile::pop() {											// pop out a card from the card pile
		Card card = cardpile.back();
		cardpile.pop_back();
		return card;
}

Card CardPile::getCard(int index) {								// return the card at "index"
	return cardpile[index];
}
int CardPile::searchCard(Card card) {							// search from a card in the cardpile
	for (it = cardpile.begin(); it != cardpile.end(); it++) {
		if (*it == card)
			return distance(cardpile.begin(), it);
	}
	return -1;
}
unsigned int CardPile::getNum() {										// get the size of the cardpile
	return cardpile.size();
}
void CardPile::sortCard() {										// sort the cards to descending order by its numeric value
	sort(cardpile.begin(), cardpile.end(), compFunction);
}

void CardPile::listShow() {										// show every card on the console as a list (vertical)
	for (unsigned int i = 0; i < cardpile.size(); i++) {
		cout << i << ": " << cardpile[i].nameOf() << endl;
	}
}

void CardPile::show() {											// show every card on the console horizontally
	for (unsigned int i = 0; i < cardpile.size(); i++) {
		cout << " ___  ";
	}
	cout << endl;
	for (unsigned int i = 0; i < cardpile.size(); i++) {
		cout << "|" << setw (5) << cardpile[i].nameOf() << "| ";
	}
	cout << endl;
	for (unsigned int i = 0; i < cardpile.size(); i++) {
		if (cardpile[i].getSuit() == Diamond) cout << "| /\\| ";
		else if (cardpile[i].getSuit() == Heart) cout << "|(`)| ";
		else if (cardpile[i].getSuit() == Club) cout << "| O | ";
		else cout << "| ^ | ";
	}
	cout << endl;
	for (unsigned int i = 0; i < cardpile.size(); i++) {
		if (cardpile[i].getSuit() == Diamond) cout << "|_\\/| ";
		else if (cardpile[i].getSuit() == Heart) cout << "|_\\_| ";
		else if (cardpile[i].getSuit() == Club) cout << "|O,O| ";
		else cout << "|(,)| ";
	}
	cout << endl << endl;
}

void CardPile::showUnknown() {									// show the cards as unknown
	for (unsigned int i = 0; i < cardpile.size(); i++) {
		cout << " ___  ";
	}
	cout << endl;
	for (unsigned int i = 0; i < cardpile.size(); i++) {
		cout << "|?  | ";
	}
	cout << endl;
	for (unsigned int i = 0; i < cardpile.size(); i++) {
		cout << "| ? | ";
	}
	cout << endl;
	for (unsigned int i = 0; i < cardpile.size(); i++) {
		cout << "|__?| ";
	}
	cout << endl << endl;
}
