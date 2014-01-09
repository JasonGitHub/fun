/*
 * round.cpp
 *
 *  Created on: Dec 10, 2010
 *      Author: jason
 */
#include "round.hpp"

void Round::play() {
	river(turn(flop(first())));
	Judge judge(*players,board);
	judge.result();
}

bool Round::first() {
	bool continue_flag;
	cout << endl << "**********************************************************************************" << endl;
	        cout << "::::::::::::::::::::::::::::::::FIRST DEAL BEGINS:::::::::::::::::::::::::::::::::" << endl;
	        cout << "**********************************************************************************" << endl << endl;

	players -> giveCards(poker);											// give hole cards to the players
	players -> showPlayersMoney();

	players -> getPlayer(SmallBlind).blindBet(SMALLBLIND_BET,board);		// automatically bet for small blind and big blind
	players -> getPlayer(BigBlind).blindBet(BIGBLIND_BET,board);
	players -> firstbet(board,bet_table,BIGBLIND_BET);						// run the first deal

	continue_flag = !(players -> checkForStatus(ALLIN)) && players -> checkNormal();	// if player all in, then show turn and river cards, and skip other deals

	if (continue_flag == false) {
		board.flop(poker);
		board.turn(poker);
		board.river(poker);
		board.listShow();
		players -> showPlayersCards();

	}

	return continue_flag;
}

bool Round::flop(bool continue_flag) {
	if (continue_flag == false) return false;
	cout << endl << "**********************************************************************************" << endl;
	        cout << ":::::::::::::::::::::::::::::::::FLOP DEAL BEGINS:::::::::::::::::::::::::::::::::" << endl;
	        cout << "**********************************************************************************" << endl << endl;
	bet_table.clear();
	board.flop(poker);
	board.listShow();
	players -> bet(board,bet_table,BIGBLIND_BET);

	continue_flag = !(players -> checkForStatus(ALLIN)) && players -> checkNormal();

	if (continue_flag == false) {
		board.turn(poker);
		board.river(poker);
		board.listShow();
		players -> showPlayersCards();
	}

	return continue_flag;
}

bool Round::turn(bool continue_flag) {
	if (continue_flag == false) return false;
	cout << endl << "**********************************************************************************" << endl;
	        cout << "::::::::::::::::::::::::::::::::::TURN DEAL BEGINS::::::::::::::::::::::::::::::::" << endl;
	        cout << "**********************************************************************************" << endl<< endl;

	bet_table.clear();
	board.turn(poker);
	board.listShow();
	players -> bet(board, bet_table, BIGBLIND_BET);

	continue_flag = !(players -> checkForStatus(ALLIN)) && players -> checkNormal();

	if (continue_flag == false) {
		board.river(poker);
		board.listShow();
		players -> showPlayersCards();
	}

	return continue_flag;

}

void Round::river(bool continue_flag) {
	if (continue_flag == false) return;
	cout << endl << "**********************************************************************************" << endl;
	        cout << "::::::::::::::::::::::::::::::::::RIVER DEAL BEGINS:::::::::::::::::::::::::::::::" << endl;
	        cout << "**********************************************************************************" << endl << endl;

	bet_table.clear();
	board.river(poker);
	board.listShow();
	players -> bet(board, bet_table, BIGBLIND_BET);

	continue_flag = !(players -> checkForStatus(ALLIN)) && players -> checkNormal();

	board.listShow();
	players -> showPlayersCards();

}
