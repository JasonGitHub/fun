/*
 * players.cpp
 *
 *  Created on: Dec 9, 2010
 *      Author: jason
 */
#include "players.hpp"

void Players::setRoles(int dealer) { // set the role of each player in "players"
	int smallBlind = (dealer - 1 >= 0) ? dealer - 1 : num_players + (dealer - 1);
	int bigBlind  = (smallBlind - 1 >= 0) ? smallBlind - 1 : num_players+ (smallBlind - 1);
	for (it = players.begin(); it != players.end(); it++) {
		(*it)-> setRole(Ordinary);
	}
	players[dealer]->setRole(Dealer);
	players[smallBlind]->setRole(SmallBlind);
	players[bigBlind]->setRole(BigBlind);
	lastdealer = dealer;
}


void Players::giveCards(Poker &poker) { // give hole cards to each player
	for (it = players.begin(); it != players.end(); it++) {
		(*it)->addHoleCards(poker.getHoleCard());
	}
}

void Players::addCardforAll(CardPile cards){ // give a cardpile of cards to each player
	for (it = players.begin(); it != players.end(); it++) {
		(*it)->addHoleCards(cards);
		(*it)->sortHoleCards();
	}
}

void Players::showPlayersCards() {	// show all players' cards
	for (it = players.begin(); it != players.end(); it++) {
		(*it)->showCards();
	}
}

void Players::showPlayersMoney() { // show all players' money
	for (it = players.begin(); it != players.end(); it++) {
		(*it)->showMoney();
	}
}

void Players::showPlayersRole() { // show all players' role
	for (it = players.begin(); it != players.end(); it++) {
		(*it)->showRole();
	}
}

void Players::initRoles() { // initiate the roles by randomly choose a dealer
	int dealer = randomGen(num_players);
	setRoles(dealer);
}

void Players::changeRoles() { // the dealer button rotates clockwise after each hand, "Small Blind" and "Big Blind" will be changed subsequently
	int dealer = (lastdealer + 1 < num_players)? lastdealer + 1 : (lastdealer + 1) % num_players;
	setRoles(dealer);
}

void Players::clearAllPlayerInfo() { // clear status, holecards and role for each player and get them ready for next round
	for (it = players.begin(); it != players.end(); it++) {
		(*it)->clearStatus();
		(*it)->clearHand();
		(*it)->clearRole();
	}
}

int Players::size() { // return the size of players
	return num_players;
}

int Players::getNumPlayers(int min,int max) { // get how many players should be involved in the game from user
	int num_players;
	while (true) {
		num_players = getInteger();
		if (num_players >= min && num_players <= max) break;
		else cout << "The number of players should be " << min << " - " <<  max << "." << endl;
	}
	return num_players;
}

Player& Players::getPlayer(Role role) {	// return a specific player found by Role
	for (it = players.begin(); it != players.end(); it++) {
		if((*it)->getRole() == role) return *(*it);
	}
	return *(*it);
}

Player& Players::getPlayer(int index) {	// return a specific player at "index"
	return *(players[index]);
}

Player& Players::getPlayerbyId(int id) { // return a player by id
	for (it = players.begin(); it != players.end(); it++) {
		if ((*it)->getId() == id) return *(*it);
	}
	return *(*it);
}

bool Players::checkForStatus(Status status) { // check if there's any player holds a specific status
	for (it = players.begin(); it != players.end(); it++) {
		if ((*it)->getStatus() == status)
			return true;
	}
	return false;
}

bool Players::checkNormal() { // check if there are at least two normal players to play
	int normal = 0;
	for (it = players.begin(); it != players.end(); it++) {
		if ((*it)->getStatus() == NORMAL) normal++;
	}
	if (normal >= 2) return true; else return false;
}

void Players::firstbet(Board &board, map<int, int> &bet_table, int minbet) { // run the first bet in a round
	for (it = players.begin(); it != players.end(); it++) {
		if ((*it)->getRole() != SmallBlind && (*it)->getRole() != BigBlind) {
			minbet = (*it)->action(board, bet_table, minbet);
		}
	}
}

void Players::bet(Board &board, map<int, int> &bet_table, int minbet) { // run the bet afterwards
	while (true) {
		for (it = players.begin(); it != players.end(); it++) {
			if ((*it)->getStatus() != FOLD && (*it)->getStatus() != ALLIN) {
				minbet = (*it)->action(board, bet_table, minbet);
			}
			if (checkEquality(bet_table) && bet_table.size() == players.size())
				return;
		}

		for (it = players.begin(); it != players.end(); it++) {
			if ((*it)->getStatus() == ALLIN)
				bet_table.erase((*it)->getId());
		}
		if (checkEquality(bet_table) || bet_table.size() == 0 || !checkNormal())
			return;
	}
}

bool Players::checkEquality(map<int, int> &bet_table) { // check if all players' bet reach consensus

	map<int, int>::iterator it;
	int last = bet_table.begin() -> second;
	for (it = bet_table.begin(); it != bet_table.end(); it++) {
		if (it -> second != last)
			return false;
		last = it -> second;
	}
	return true;
}
