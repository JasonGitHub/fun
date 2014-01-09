/*
 * aiplayer.hpp
 *
 *	Class Aiplayer is used to simulate an AI player (computer player) in the game
 *
 *  Created on: Dec 10, 2010
 *      Author: jason
 */

#include "player.hpp"

#pragma once

class Aiplayer: public Player { // derived from class Player and override the "action" functions to perform as an AI player
private:
	void showUnknown();
public:
	Aiplayer() { // Call default base class constructor
	}

	Aiplayer(bool autoset) :
		Player(true) { // Call Player(bool) constructor
	}

	// AI player action in game
	int action(Board &board, map<int, int> &bet_table, int minbet);
	int call(Board &board, map<int, int> &bet_table, int minbet);
	int raise(Board &board, map<int, int> &bet_table, int minbet);
	void fold();
	void blindBet(int bet, Board &board);
};
