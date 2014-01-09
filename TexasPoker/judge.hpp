/*
 * judge.hpp
 *
 *	Class "Judge" simulates a referee (or judge) in the game, and will decide who wins and distribute the pot money to winners
 *
 *  Created on: Dec 10, 2010
 *      Author: jason
 */
#include "cardpile.hpp"
#include "players.hpp"
#include "board.hpp"
#include "card.hpp"
#include <vector>
#include <map>

#pragma once

class Judge {

private:
	Players* players;
	Board* board;
	map<int,int> score_table; // maintain a table of how many pairs each player holds
	vector<int> win_table;	// put the winners in this table
	map<int,int> :: iterator it;

	int checkPairs(CardPile cards); // private function used by result() to check pairs that players hold

public:
	Judge(Players &players, Board &board){
		this -> players = &players;
		this -> board = &board;
		this -> players -> addCardforAll(board);
	}
	void result();
};
