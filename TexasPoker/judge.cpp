/*
 * judge.cpp
 *
 *  Created on: Dec 10, 2010
 *      Author: jason
 */

#include "judge.hpp"

void Judge::result() { // show the result of a round
	cout << endl << "The result of the game:" << endl;
	for (int i = 0; i < players -> size(); i++) {
		if (players->getPlayer(i).getStatus() != FOLD) {
			int pairs = checkPairs(players->getPlayer(i).getHoleCards());
			int id = players->getPlayer(i).getId();
			cout << "Player <" << id << "> have " << pairs << " pair." << endl;
			score_table[id] = pairs;
		}
	}

	if (score_table.size() == 0) { // if everybody folds, system will distribute the pot money equally to everybody
		cout << "No one wins." << endl;
		int award = board->getPot() / players->size();
		board->removeMoney();
		for (int i = 1; i <= players->size(); i++) {
			players->getPlayerbyId(i).winMoney(award);
		}
		return;
	}

	int max = 0; // check for player holds the most pairs
	for (it = score_table.begin(); it != score_table.end(); it++) {
		if (it->second > max)
			max = it->second;
	}
	int win_num = 0;
	for (it = score_table.begin(); it != score_table.end(); it++) {
		if (it->second == max) {
			win_table.push_back(it ->first);
			win_num++;
		}
	}

	int award = board->getPot() / win_num; // send the money to winners
	board->removeMoney();
	for (unsigned int i = 0; i < win_table.size(); i++) {
		players->getPlayerbyId(win_table[i]).winMoney(award);
		cout << "Player <" << win_table[i] << "> wins $" << award << "."
				<< endl;
	}
}

int Judge::checkPairs(CardPile cards) { // check how many pairs each player holds
	int pairs = 0;
	for (unsigned int i = 1; i < cards.getNum(); i++) {
		if (cards[i].getCardinal() == cards[i - 1].getCardinal()) {
			pairs++;
			i++;
		}
	}
	return pairs;
}
