/*
 * round.hpp
 *
 *  Class Round is used to simulate one round in a game of Texas Hold'em
 *
 *  Created on: Dec 8, 2010
 *      Author: jason
 */

#include "players.hpp"
#include "poker.hpp"
#include "board.hpp"
#include "judge.hpp"
#include <map>

#pragma once

#define BIGBLIND_BET 2
#define SMALLBLIND_BET 1

class Round {
private:
	Players* players;
	Poker poker;
	Board board;
	map<int,int> bet_table; // maintain a table of each player's bet
	bool first(); // run the first deal
	bool flop(bool continue_flag); // run the flop deal
	bool turn(bool continue_flag); // run the turn deal
	void river(bool continue_flag); // run the river deal

public:
	Round(Players &players):players(&players){}
	void play(); // play this round
};
