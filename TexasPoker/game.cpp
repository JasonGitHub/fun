/*
 * game.cpp
 *
 *  Created on: Dec 10, 2010
 *      Author: jason
 */

#include "game.hpp"

void Game::play() {															// used to play the Texas Hold'em game

	players.initRoles(); // run the first round, which randomly select the dealer
	players.showPlayersRole();
	Round firstround(players);
	firstround.play();
	if(quitGameOrNot()) return;

	while (true) { // run the rounds afterwards, the dealer button will circulate clockwise
		cout << endl << "**********************************************************************************" << endl;
		        cout << "#############################   New Round Begins   ###############################" << endl;
		        cout << "**********************************************************************************" << endl << endl;
		players.clearAllPlayerInfo();
		players.changeRoles();
		players.showPlayersRole();
		Round round(players);
		round.play();
		if(quitGameOrNot()) break; // check if the user wants to exit the game
	}

}

bool Game::quitGameOrNot() {												// check if the user wants to exit the game
	while (true) {
		cout << endl << "Want to quit the game?" << endl << "0: No." << endl
				<< "1: Yes." << endl;
		int choice = getInteger();
		if (choice == 0)
			return false;
		else if (choice == 1) {
			cout << "You have exit the game." << endl;
			return true;
		} else
			cout << "Please select from 0 and 1." << endl;
	}
}
