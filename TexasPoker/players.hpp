/*
 * players.hpp
 *
 *	Class Players encapsulates several players including both human and computer players
 *	and act as a controller of all players in the game
 *
 *  Created on: Dec 8, 2010
 *      Author: jason
 */
#include "player.hpp"
#include "aiplayer.hpp"
#include "tools.hpp"
#include <vector>
#include <map>

#pragma once

const int min_num_player = 3;  // the maximun and minimun players allowed by the system
const int max_num_player = 8;  // should not be changed by any user, I made it const

class Players {

private:
	vector<Player*> players;
	vector<Player*> :: iterator it;
	int lastdealer;		// keep a record of who is the dealer in last round
	int num_players;	// keep the size of players as a data member will increase efficiency as other object use players.size() very frequently

	void setRoles(int dealer); // inner function to set the player roles

public:

	Players() {	// build players
		int autoset;
		int min_players = min_num_player;
		int max_players = max_num_player;
		cout << "Please set the number of players (" << min_players << " - " << max_players << " players):"; // get the total number of players
		num_players = getNumPlayers(min_players,max_players);

		cout << "How many computer players do you want? ( 0 - " << num_players - 1 << " computer players):";  // get the number of computer players
		int num_aiplayers = getNumPlayers(0,num_players - 1);
		int num_humanplayers = num_players - num_aiplayers;

		while (true) {	// get the user's choice for "automatic mode" or "manual mode"
			cout << "Automatically set start money for all players?" << endl
				 << "0: No." << endl
				 << "1: Yes." << endl;
			autoset = getInteger();
			if (autoset == 0 || autoset == 1) break;
			else cout << "Please select from 0 and 1." << endl;
		}

		for (int i = 0; i < num_humanplayers; i++) { // build human players
			if (autoset == 0) {
				players.push_back(new Player());
			} else {
				players.push_back(new Player(true));
			}
		}

		for (int i = 0; i < num_aiplayers; i++) {	// build computer players
			if (autoset == 0) {
				players.push_back(new Aiplayer());
			} else {
				players.push_back(new Aiplayer(true));
			}
		}
	}

	~Players() {
		for (it = players.begin(); it != players.end(); it++) { // free memory
			delete (*it);
		}
	}

	void giveCards(Poker &poker); // give hole cards to each player
	void addCardforAll(CardPile cards); // give a cardpile of cards to each player
	void showPlayersCards(); // show all players' cards
	void showPlayersMoney(); // show all players' money
	void showPlayersRole(); // show all players' role
	void initRoles(); // initiate the roles by randomly choose a dealer
	void changeRoles();  // the dealer button rotates clockwise after each hand, "Small Blind" and "Big Blind" will be changed subsequently
	void clearAllPlayerInfo(); // clear status, holecards and role for each player and get them ready for next round
	int size(); // return the size of players
	int getNumPlayers(int min,int max); // get how many players should be involved in the game from user
	Player& getPlayer(Role role); // return a specific player found by Role
	Player& getPlayer(int index); // return a specific player at "index"
	Player& getPlayerbyId(int id); // return a player by id
	bool checkForStatus(Status status); // check if there's any player holds a specific status
	bool checkNormal();  // check if there are at least two normal players to play
	void firstbet(Board &board, map<int,int> &bet_table, int minbet); // run the first bet in a round
	void bet(Board &board, map<int, int> &bet_table, int minbet); // run the bet afterwards
	bool checkEquality(map<int, int> &bet_table); // check if all players' bet reach consensus
};
