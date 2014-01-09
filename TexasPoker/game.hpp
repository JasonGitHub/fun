/*
 * game.hpp
 *
 *  Class Game is used to simulate the entire game of Texas Hold'em, which includes several "rounds"
 *
 *  Created on: Dec 8, 2010
 *      Author: jason
 */
#include "round.hpp"
#include "players.hpp"

#pragma once

class Game {

private:
	Players players; // include the players in the Game, because players should maintain their "money" through different rounds
	bool quitGameOrNot(); // check if the user wants to quit the game

public:
	void play(); // run the game
};
