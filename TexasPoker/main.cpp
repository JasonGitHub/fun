/*
 * main.cpp
 *
 *	This game is used to simulate a revised version of "Texas Hold'em"
 *	It have the following classes:
 *
 *	Player	: simulates a human player
 *	Ailayer	: simulates a computer player
 *	Players	: encapsulate several players (polymorphic) which includes both human player and computer
 *	Card	: simulates a game card
 *	CardPile: encapsulate multiple game cards
 *	Board	: derived from CardPile. simulate the common board in the game which is actually "Common Cards" + "Common Money"
 *	Poker	: derived from CardPile. simulate the poker deck used in the game. which include the 52 game card from "♦A" to "♠K"
 *	Judge	: simulates a judge (or referee) in the game, and decide who win or lost.
 *	Round	: simulates a round in the game
 *	Game	: simulates the entire game, which includes several rounds of Texa Hold'em
 *
 *
 *  Created on: Dec 6, 2010
 *      Author: jason
 */

#include "game.hpp"

using namespace std;

int main() {
	srand(time(0));
	gameBanner(); // Prints my Beautiful Game Banner : ) !!!
	Game game; // Build the game
	game.play(); // Play the game
	return 0;
}
