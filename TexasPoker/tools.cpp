//                  -*- mode:c++; tab-width:4 -*-
// File: tools.cpp - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  the tools library.
//  Assorted utility routines for use in C++ programs.
//  Modified by jason
//  Dec 6, 2010
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#include "tools.hpp"

// --------------------------------------------------------------------------
// I/O Utilities. -----------------------------------------------------------
// ---------------------------------------------------------------------------
// Used to flush the cin buffer as in cin >> x >> flush;  or cin >> flush;
istream&
flush( istream& is ) {  return is.seekg( 0, ios::end ); }

// ---------------------------------------------------------------------------
// Print a neat header on the output.

void
fbanner( ostream& fout )
{   char date[16], time[10];
    when(date, time);
    fout << "\n---------------------------------------------------------------\n"
         << "\t" << NAME
         << "\n\t" << CLASS << "\n\t" <<  date << "\t" << time << endl
         << "---------------------------------------------------------------\n";
}

// ---------------------------------------------------------------------------
//  Print termination message.

void bye( void ) {
    cout << "\n---------------------------------------------------------------"
            "\nNormal termination.\n" ;
}

// --------------------------------------------------------------------------
//  This is a handy function for messages of all sorts.
//  It formats and prints a message.
//  params: a format followed by a variable number of data items to print.

void
say (const char* format, ...)
{   va_list vargs;                               // optional arguments

    va_start(vargs, format);
    vfprintf(stdout, format, vargs);
    fprintf(stdout, "\n");
}


// --------------------------------------------------------------------------
// Delay progress of program for some number of seconds using a "busy wait".

void
delay( int seconds )
{
    do { seconds = sleep( seconds ); } while (seconds > 0);
}

// ----------------------------------------------------------------------------
//  Error handling and error recovery.
//-----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// This function is for error messages.
//    It takes a format argument followed by any number of data arguments.
//    It formats and prints an error message, then exits.

void
fatal (const char* format, ...)
{   va_list vargs;                               // optional arguments

    cout << flush;
    va_start(vargs, format);
    vfprintf(stdout, format, vargs);
    fprintf(stdout, "\n");
    exit(1);
}

// ----------------------------------------------------------------------------
// Routines for handling the time and date.
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Store the current date and time in the arguments.
//      System's date format is: "Fri Jun  9 10:15:55 1995\n"
//      After extraction, date is: "Fri Jun  9 1995"    hour is: "10:15:55"

void
when( cstring date, cstring hour)
{
    time_t now;           // Stores an integer encoding of the date and time.
    char* nowstring;    // Stores the date and time in a readable form.

    now = time(NULL);              // Get the date and time from the system.
    nowstring = ctime(&now);                   // Convert to string form.
    strncpy( date, nowstring, 10);             // Extract day, month, date.
    strncpy( &date[10], &nowstring[19], 5);    // Extract space and year.
    date[15]  = '\0';                          // Add the string terminator.
    strncpy( hour, &nowstring[11], 8);         // Copy hour:minutes:seconds.
    hour[8]  = '\0';                           // Add the string terminator.
}

// ----------------------------------------------------------------------------
// Store the current date in the argument and return a pointer to it.
//      date format is: "Fri Jun  9 1995"

cstring
today( cstring date )
{
    time_t now;          // Stores an integer encoding of the date and time.
    cstring nowstring;   // Stores the date and time in a readable form.

    now = time(NULL);              // Get the date and time from the system.
    nowstring = ctime(&now);                   // Convert to string form.
    strncpy( date, nowstring, 10);             // Extract day, month, date.
    strncpy( &date[10], &nowstring[19], 5);    // Extract space and year.
    date[15]  = '\0';                          // Add the string terminator.
    return( date );
}

// ----------------------------------------------------------------------------
// Store the current time in hour and return a pointer to it.
//      hour format is: "10:15:55"

cstring
oclock( cstring hour)
{
    time_t now;          // Stores an integer encoding of the date and time.
    cstring nowstring;   // Stores the date and time in a readable form.

    now = time(NULL);              // Get the date and time from the system.
    nowstring = ctime(&now);              // Convert to string form.
    strncpy( hour, &nowstring[11], 8);    // Extract hour, minutes, seconds.
    hour[8]  = '\0';                      // Add the string terminator.
    return( hour );
}

// ----------------------------------------------------------------------------
// A more secure way to get an integer from user
// bad inputs handled

int getInteger()
{
	int value;
	while (true) {
		if (cin >> value) {
			while (!isspace(cin.get())) continue;
			return value;
		}
		else {
			cout << "Invalid input, please enter an integer:";
			cin.clear();
			while (!isspace(cin.get())) continue;
		}
	}
}

// ----------------------------------------------------------------------------
// Uniform distributed number generator
// Generate a random int between 0 and n-1, inclusive

int randomGen(int n) {
	int top = ((((RAND_MAX - n) + 1) / n) * n - 1) + n;
	int r;
	do {
		r = rand();
	} while (r > top);
	return (r % n);
}

//------------------------------------------------------------------------------
// Prints the banner of the game

void gameBanner() {
	for (int i = 0; i < 20; i++) {
		cout << endl;
	}
	cout << "**********************************************************************************" << endl;
	cout << "                                       _____                                      " << endl;
	cout << "           _____                _____ |6    |                                     " << endl;
	cout << "          |2    | _____        |5    || & & |                                     " << endl;
	cout << "          |  &  ||3    | _____ | & & || & & | _____                               " << endl;
	cout << "          |     || & & ||4    ||  &  || & & ||7    |                              " << endl;
	cout << "          |  &  ||     || & & || & & ||____9|| & & | _____                        " << endl;
	cout << "          |____Z||  &  ||     ||____S|       |& & &||8    | _____                 " << endl;
	cout << "                 |____E|| & & |              | & & ||& & &||9    |                " << endl;
	cout << "                        |____h|              |____L|| & & ||& & &|                " << endl;
	cout << "                                    _____           |& & &||& & &|                " << endl;
	cout << "                            _____  |K  WW|          |____8||& & &|                " << endl;
	cout << "                    _____  |Q  ww| | o {)|                 |____6|                " << endl;
	cout << "             _____ |J  ww| | o {(| |o o%%| _____                                  " << endl;
	cout << "            |10 & || o {)| |o o%%| | |%%%||A _  |                                 " << endl;
	cout << "            |& & &||o o% | | |%%%| |_%%%>|| ( ) |   Welcome to                    " << endl;
	cout << "            |& & &|| | % | |_%%%O|        |(_'_)|    jason's                      " << endl;
	cout << "            |& & &||__%%[|                |  |  |  Texas Hold'em                  " << endl;
	cout << "            |___0I|                       |____V|                                 " << endl;
	cout << "                                                                                  " << endl;
	cout << "                                                                                  " << endl;
	cout << "                          All rights reserved     copyright © ​2010                " << endl;
	cout << "                                                                                  " << endl;
	cout << "**********************************************************************************" << endl;
	cout << "                                                                                  " << endl;
	cout << "                                                                                  " << endl;
	cout << "                  Welcome to jason's Texas Hold'em Game!                          " <<endl;
	for (int i = 0; i < 3; i++) {
			cout << endl;
	}
}




