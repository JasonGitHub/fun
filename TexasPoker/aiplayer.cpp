/*
 * aiplayer.cpp
 *
 *  Created on: Dec 10, 2010
 *      Author: jason
 */
#include "aiplayer.hpp"

void Aiplayer::showUnknown() {
	cout << "Cards of Player <" << id << ">: " << endl;
	holecards.showUnknown();
}


int Aiplayer::action(Board &board, map<int,int> &bet_table, int minbet) {

	Action action;
	int new_minbet = minbet;
	int selection;
	cout << endl << "************************ AI Player <" << id << ">'s turn to play: ***************************" << endl;
		        cout << "**********************************************************************************" << endl;

    showUnknown();
	if (money > minbet) {
		selection = 2;
	}
	else if (money <= minbet && money > 0) {
		selection = 1;
	}
	else {
		cout << "AI Player <" << id << "> run out of money." << endl;
		fold();
		return minbet;
	}

	action = Action(randomGen(selection + 1));

	if (action == Fold) fold();															// interpret AI's selection
	else if (action == Call) new_minbet = call(board,bet_table,minbet);
	else if (action == Raise) new_minbet = raise(board,bet_table,minbet);
	else fatal ("Error in processing user choice.");

	return new_minbet;
}

int Aiplayer::call(Board &board, map<int,int> &bet_table, int minbet) {
	if (money <= minbet) {																// check if the AI player all in
		board.addMoney(money);
		bet_table[id] = money;
		cout << "AI Player <" << id << "> All in, and put $" << money << " in the pot." << endl;
		money = 0;
		status = ALLIN;
		return minbet;
	}
	else {
		money -= minbet;																// if not use standard call sequence
		board.addMoney(minbet);
		bet_table[id] = minbet;
		cout << "AI Player <" << id << "> calls and put $"<< minbet << " in the pot." << endl
			 << "AI Player <" << id << "> now have $"<< money << "." << endl;
	}
	return minbet;
}

int Aiplayer::raise(Board &board, map<int,int> &bet_table, int minbet) {

	int new_minbet = minbet;

	cout << "Player <" << id << "> raise." << endl;

	while (true) {																		// get how much money the AI player want to raise
		int raise = randomGen(money - minbet) + 1;

		if (raise >=1 && (raise+minbet) < money) {
			money -= (raise + minbet);
			board.addMoney(raise + minbet);
			bet_table[id] = raise + minbet;
			new_minbet = raise + minbet;
			cout << "AI Player <" << id << "> raise $" << raise << " and put $" << (raise+minbet) << " in the pot" << endl;
			break;
		}
		else if (raise >=1 && (raise+minbet) == money) {
			money = 0;
			board.addMoney(raise+minbet);
			bet_table[id] = raise + minbet;
			new_minbet = raise + minbet;
			cout << "AI Player <" << id << "> All in and put $" << (raise+minbet) << " in the pot" << endl;
			status = ALLIN;
			break;
		}
	}

	cout << "Player <" << id << "> now have $"<< money << "." << endl;
	return new_minbet;
}

void Aiplayer::fold() {
	status = FOLD;
	cout << "AI Player <" << id << "> have fold." << endl;
}

void Aiplayer::blindBet(int bet, Board &board) {
	cout << endl << "************************ AI Player <" << id << ">'s turn to play: ***************************" << endl;
			        cout << "**********************************************************************************" << endl;

	if (money < bet) {
		fold();
		return;
	}
	money-=bet;
	board.addMoney(bet);

	cout << "<#SYSTEM INFO#> (Blind Player) System put $"<< bet << " in pot for AI Player <" << id << ">." << endl
		     << "AI Player <" << id << "> now have $"<< money << "." << endl;
	showUnknown();
}
