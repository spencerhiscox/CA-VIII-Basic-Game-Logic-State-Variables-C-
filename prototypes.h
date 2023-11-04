/*
Copyright© Spencer Hiscox, 2023
All rights reserved
*/


#pragma once
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

struct I00percent {
	char nomNomNom[120];
	float doOver;
	bool initial, fail;
};

struct gameFiles {
	char
		dieFace[6][7][17] = { { {"  ------------  "}, {" |            | "}, {" |            | "}, {" |     @@     | "}, {" |            | "}, {" |            | "}, {"  ------------  "} },
							   {{"  ------------  "}, {" |            | "}, {" |  @@        | "}, {" |            | "}, {" |        @@  | "}, {" |            | "}, {"  ------------  "}},
							   {{"  ------------  "}, {" | @@         | "}, {" |            | "}, {" |     @@     | "}, {" |            | "}, {" |         @@ | "}, {"  ------------  "}},
							   {{"  ------------  "}, {" | @@      @@ | "}, {" |            | "}, {" |            | "}, {" |            | "}, {" | @@      @@ | "}, {"  ------------  "}},
							   {{"  ------------  "}, {" | @@      @@ | "}, {" |            | "}, {" |     @@     | "}, {" |            | "}, {" | @@      @@ | "}, {"  ------------  "}},
							   {{"  ------------  "}, {" | @@      @@ | "}, {" |            | "}, {" | @@      @@ | "}, {" |            | "}, {" | @@      @@ | "}, {"  ------------  "}} },

		handName[5][16] = { {"Three of a Kind"},
							{"Four of a Kind"},
							{"Full House"},
							{"Yahtzee"},
							{"Chance"} };
};

struct gameData {
	char playerName[21];
	unsigned char currentRolls[5] = {},
		score[11] = {},
		roundCounter = 1,
		scoreCounter = 0,
		rollCounter = 1,
		handType = 0;
	bool freezeState[5] = {};
};

struct navMarks {
	unsigned char userChoice = 0,
		roundScore = 0,
		rollCount[6] = {};

	bool noScore = false;
};

void getPlayerName(gameData*);
void dispWelcome(gameData*);

I00percent eatTheCrazy(I00percent);							//Handles user-entered text into numeric format specifier using scanf_s()

void rollDie(gameData*);
void dispRoll(gameData*, gameFiles*);						//This is the function that handles displaying the ASCII art representation of the dice roll

unsigned short int getInteger(void);						//Function specifically to get integers from user (main purpose is checks to ensure user entered
															//what they were supposed to.
void freezeDie(gameData*);									//Function works in conjunction with getInteger() to handle user freezing certain dice. This one
															//specifically handles parsing the user-entered value into individual digits which it passes to a
															//boolean array which is read by rollDie() to skip overwriting die the user has elected to freeze.
void dispScore(gameData*, bool);

unsigned char getUSChar(void);								//Function to obtain menu selection from user (and check to make sure it's a valid entry)
void checkHand(gameData*);									//Function to determine what the final roll was (three of a kind / full house / yahtzee etc.)
void calcScore(gameData*, navMarks*);						//Function to determine the score value based on what user entered as the line they want to enter
															//their score on
void updateScore(gameData*, gameFiles*);					//Function to handle what the user's choice of scoring line was (calls above 3 functions)
															//Checks if selection is valid (if user is allowed to score on the entered line) and updates the 
															//score appropriately 
void finalScore(gameData*);
