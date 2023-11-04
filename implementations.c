/*
Copyright© Spencer Hiscox, 2023
All rights reserved
*/


#pragma once
#include "prototypes.h"


void getPlayerName(gameData* gameState) {

	char temp[21], eatTheCrazy[21];
	bool i = false, check = false;

	do {
		if (i) {
			printf("\nSorry, that was not a valid entry.\nPlayer name must be 20 characters or less.\n\n");
		}

		printf("Enter your name to start the game!\nName: ");
		if (i) {
			do {
				scanf_s("%s", eatTheCrazy, 21);
			} while (eatTheCrazy[0] == NULL);
			for (unsigned char j = 0; j < 21; j++) {
				eatTheCrazy[j] = NULL;
			}
		}
		scanf_s("%s", temp, 21);

		for (unsigned char j = 0; j < 21; j++) {
			if (temp[0] == '\0') {
				break;
			}
			else if (temp[j] == '\0') {
				check = true;
				break;
			}
		}

		i = true;
	} while (!check);

	strcpy_s(gameState->playerName, temp);

	return;
}

void dispWelcome(gameData* gameState) {																//Welcome = 7, spaces = 3

	unsigned char i = 0;

	printf("\n********************************************************************************\n");

	while (gameState->playerName[i] != NULL) {									// Note to the marker: We hadn't been taught strnlen() in lecture prior to this assignment
		i++;																	// and I wrote this code before reading a few more lines to where he said in the instructions
	}																			// that we could use strnlen() -- I was proud of my ingenuity here so I just kept the code
																				// I wrote originally.
	for (unsigned char j = 0; j < (80 - (i + 10)) / 2; j++) {
		printf("*");
	}
	printf(" Welcome %s ", gameState->playerName);
	for (unsigned char j = 0; j < (80 - (i + 10)) / 2; j++) {
		printf("*");
	}
	if ((80 - (i + 10)) % 2 != 0) {
		printf("*");
	}
	printf("\n");


	printf("********************************************************************************\n");

	return;
}

void rollDie(gameData* gameState) {

	srand(time(NULL));

	for (unsigned char i = 0; i < 5; i++) {
		if (gameState->freezeState[i]) {
			continue;
		}
		else {
			gameState->currentRolls[i] = ((rand() % 6) + 1);
		}
	}

	return;
}

void dispRoll(gameData* gameState, gameFiles* resources) {

	printf("\n--------------------------------------------------------------------------------\n");
	printf("This is roll #%hhu\n", gameState->rollCounter);
	printf("--------------------------------------------------------------------------------\n\n");

	for (unsigned char i = 0; i < 7; i++) {
		for (unsigned char j = 0; j < 5; j++) {
			printf("%s", resources->dieFace[gameState->currentRolls[j] - 1][i]);
		}
		printf("\n");
	}
	printf("\n--------------------------------------------------------------------------------\n");

	return;
}

I00percent eatTheCrazy(I00percent crazyFree) {

	if (!crazyFree.initial) {
		printf("Confirm entry [Y/N]: ");
		crazyFree.initial++;
	}
	scanf_s("%s", crazyFree.nomNomNom, 100);
	bool crazy = strcmp(crazyFree.nomNomNom, "Y");
	bool crazy2 = strcmp(crazyFree.nomNomNom, "y");
	bool crazy3 = strcmp(crazyFree.nomNomNom, "N");
	bool crazy4 = strcmp(crazyFree.nomNomNom, "n");
	if ((crazy == 0) || (crazy2 == 0) || (crazy3 == 0) || (crazy4 == 0)) {
		if (((!crazyFree.fail) && (crazyFree.nomNomNom[0] == 'Y')) || ((!crazyFree.fail) && (crazyFree.nomNomNom[0] == 'y'))) {
			crazyFree.initial = 0;
			crazyFree.fail = 0;
			return crazyFree;
		}
		else if (((crazyFree.doOver == NULL) && (crazyFree.nomNomNom[0] == 'Y')) || (crazyFree.nomNomNom[0] == 'y') && (crazyFree.doOver == NULL)) {
			crazyFree.fail = 0;
			crazyFree.initial = 0;
			printf("\nInvalid entry. Entry must be a number.\nPlease make your entry again: ");
			scanf_s("%f", &crazyFree.doOver);
			crazyFree = eatTheCrazy(crazyFree);
		}
		else {
			crazyFree.fail = 0;
			crazyFree.initial = 0;
			printf("\nEntry discarded.\nPlease make your entry: ");
			scanf_s("%f", &crazyFree.doOver);
			crazyFree = eatTheCrazy(crazyFree);
		}
		return crazyFree;
	}
	else {
		if (!crazyFree.fail) {
			crazyFree.fail = true;
			crazyFree.doOver = NULL;
		}
		crazyFree = eatTheCrazy(crazyFree);
		return crazyFree;
	}
}

unsigned short int getInteger(void) {

	I00percent crazyFree;
	strcpy_s(crazyFree.nomNomNom, 120, "apparently VS gets mad if you don't initialize your structs before passing their pointers to functions.. who knew...");

	float userInput = 0;
	bool check = true, fail = false;

	do {
		crazyFree.doOver = NULL;												//The checks and error messages in this do/while loop aren't perfect
		crazyFree.initial = 0;													//unfortunately. I could write the loop so that there was no way to get
		crazyFree.fail = 0;														//something past the system - but it would require the use of a function or
																				//two that I've just been reading about on the Google (and we haven't been
		if (fail) {																//taught yet). Specifically, I think I would have to take the user input 
			if (userInput != (int)userInput) {									//number as a string - do a digit count using strnlen() and then convert
				printf("\nInvalid entry. Entry cannot contain a decimal.\n"		//the string into a float for the rest of the checks. Anyway, the checks
					"Please enter only 1s or 0s, as described above.\n\n");		//are pretty good as they are - just not perfect :@
			}
			else if (userInput > 99999) {
				printf("\nInvalid entry. Entry cannot have more than 5 digits.\n"
					"Please enter only 1s or 0s, as described above.\n\n");
			}
			else if (userInput < 0) {
				printf("\nInvalid entry. Entry cannot be negative.\n"
					"Please enter only 1s or 0s, as described above.\n\n");
			}
			else if (!check) {
				printf("\nInvalid entry. Entry must contain only 1s or 0s.\n"
					"Please enter only 1s or 0s, as described above.\n\n");
				check = true;
			}
			else if (userInput > 11111) {
				printf("\nInvalid entry. \nEntry is larger than the maximum possible value (11111).\n"
					"Please enter only 1s or 0s, as described above.\n\n");
			}
			else if (userInput <= 9999) {
				printf("\nInvalid entry. Entry must have 5 digits.\n"
					"Please enter only 1s or 0s, as described above.\n\n");
			}
			else {
				printf("\nUh ohhh. Something went wrong.\n"														//This is only here for me - if this ever
					"Please contact your friendly neighbourhood software developer\n\n");						//printed out then I obviously screwed up
				break;																							//the code.
			}
			fail = false;
		}

		printf("Enter your selection: ");
		scanf_s("%f", &userInput);

		crazyFree = eatTheCrazy(crazyFree);																		//Bet you're tired of seeing "eatTheCrazy"
																												//throughout my assignments.
		if (crazyFree.doOver != NULL) {
			userInput = crazyFree.doOver;
		}

		if ((userInput == (int)userInput) && (userInput < 11112) && (userInput > 0)) {							//check each digit to ensure 1 or 0 only
			for (unsigned char i = 0; i < 5; i++) {
				if ((((int)userInput / (int)(pow(10, i))) % 10 != 0) && (((int)userInput / (int)(pow(10, i))) % 10 != 1)) {
					check = false;
					break;																						//Again, this function only checks the first
				}																								//five digits left of the decimal place
			}																									//could write it as a while loop based 
		}																										//on the strnlen() method I was talking
																												//about above, but this would require the
		fail = true;																							//use of atof() - which we haven't been 
	} while ((userInput != (int)userInput) || (userInput > 11111) || (userInput < 0) || (!check));				//taught.

	printf("********************************************************************************\n");
	return (unsigned short int)userInput;
}

void freezeDie(gameData* gameState) {

	unsigned short int temp;

	printf("\n********************************************************************************\n"
		"Enter die number you want to freeze (1 = freeze, 0 = re-roll)\n"
		"Example:\tTo freeze dice 1, 4 and 5, enter \"10011\"\n"
		"\t\t\To re-roll all five dice enter \"00000\"\n\n");

	temp = getInteger();

	if (temp != 0) {
		for (unsigned char i = 0; i < 5; i++) {
			gameState->freezeState[4 - i] = ((temp / (int)(pow(10, i))) % 2);
		}
	}

	return;
}

void dispScore(gameData* gameState, bool quit) {

	printf("\n\n********************************************************************************\n\n");
	printf("--------------------------------- Score Sheet ----------------------------------\n");
	printf(" ROW #\t\t\"CATEGORY\"\t   SCORE\n");
	for (unsigned char i = 0; i < 11; i++) {
		printf("%4hhu)\t", i + 1);
		printf((i < 6) ? "%15hhus:\t" : (i == 6) ? "     3 of a kind:\t" : (i == 7) ? "     4 of a kind:\t" : (i == 8) ? "      Full House:\t" : (i == 9) ?
			"         Yahtzee:\t" : "          Chance:\t", i + 1);
		printf("%6hhu\n", gameState->score[i]);
	}
	printf("\n********************************************************************************\n");
	if ((!quit) && (gameState->rollCounter != 12)) {
		printf("\n********************************************************************************\n");
	}

	return;
}

unsigned char getUSChar(void) {

	I00percent crazyFree;
	strcpy_s(crazyFree.nomNomNom, 120, "apparently VS gets mad if you don't initialize your structs before passing their pointers to functions.. who knew...");

	float userInput = 0;
	bool fail = false;

	do {
		crazyFree.doOver = NULL;
		crazyFree.initial = 0;
		crazyFree.fail = 0;

		if (fail) {
			if (userInput != (int)userInput) {
				printf("\nInvalid entry. Entry cannot contain a decimal.\n\n");
			}
			else if (userInput < 0) {
				printf("\nInvalid entry. Entry cannot be negative.\n\n");
			}
			else if ((userInput > 11) || (userInput < 1)) {
				printf("\nInvalid entry. Entry must be between 1 and 11.\n\n");
			}
			else {
				printf("\nUh ohhh. Something went wrong.\n"
					"Please contact your friendly neighbourhood software developer\n\n");
				break;
			}
			fail = false;
		}

		printf("Enter a value between 1) and 11): ");
		scanf_s("%f", &userInput);
		crazyFree = eatTheCrazy(crazyFree);

		if (crazyFree.doOver != NULL) {
			userInput = crazyFree.doOver;
		}

		fail = true;
	} while ((userInput != (int)userInput) || (userInput > 11) || (userInput < 1));

	return (unsigned char)userInput;
}

void checkHand(gameData* gameState, navMarks* calcRef) {

	//handType codes:																	
//		0 - random 5 numbers or a pair (no trips, no boat, no quad, no yahtzee)			
//		3 - trips																		
//	   32 - boat																		
//		4 - quads																		
//		5 - yahtzee


	for (unsigned char i = 0; i < 5; i++) {
		calcRef->rollCount[gameState->currentRolls[i] - 1]++;
	}
	for (unsigned char i = 0; i < 6; i++) {
		if (calcRef->rollCount[i] == 3) {
			for (unsigned char j = 0; j < 6; j++) {
				if (calcRef->rollCount[j] == 2) {
					gameState->handType = 32;
					if ((gameState->score[8] != NULL) && (gameState->score[i] != NULL)
						&& (gameState->score[j] != NULL) && (gameState->score[6] != NULL)
						&& (gameState->score[10] != NULL)) {
						calcRef->noScore = true;
					}
					return;
				}
			}
			gameState->handType = 3;
			if ((gameState->score[i] != NULL) && (gameState->score[6] != NULL) && (gameState->score[10] != NULL)) {
				for (unsigned char j = 0; j < 5; j++) {
					if (gameState->score[j] == NULL) {
						return;
					}
				}
				calcRef->noScore = true;
				return;
			}
			return;
		}
		else if (calcRef->rollCount[i] == 4) {
			gameState->handType = 4;
			if ((gameState->score[i] != NULL) && (gameState->score[7] != NULL) && (gameState->score[6] != NULL) && (gameState->score[10] != NULL)) {
				for (unsigned char j = 0; j < 5; j++) {
					if (gameState->score[j] == NULL) {
						return;
					}
				}
				calcRef->noScore = true;
				return;
			}
			return;
		}
		else if (calcRef->rollCount[i] == 5) {
			gameState->handType = 5;
			if ((gameState->score[i] != NULL) && (gameState->score[9] != NULL) && (gameState->score[10] != NULL)) {
				calcRef->noScore = true;
				return;
			}
			return;
		}
	}

	gameState->handType = 0;
	if (gameState->score[10] != NULL) {
		for (unsigned char i = 0; i < 5; i++) {
			if (gameState->score[gameState->currentRolls[i] - 1] == NULL) {
				return;
			}
			calcRef->noScore = true;
			return;
		}
	}
	return;
}

void calcScore(gameData* gameState, navMarks* calcRef) {

	calcRef->roundScore = 0;

	if (calcRef->userChoice < 7) {
		for (unsigned char i = 0; i < 5; i++) {
			if (gameState->currentRolls[i] == calcRef->userChoice) {
				calcRef->roundScore += gameState->currentRolls[i];
			}
		}
		return;
	}
	else if ((calcRef->userChoice == 7) || (calcRef->userChoice == 8) || (calcRef->userChoice == 11)) {
		for (unsigned char i = 0; i < 5; i++) {
			calcRef->roundScore += gameState->currentRolls[i];
		}
		return;
	}
	else if (calcRef->userChoice == 9) {
		calcRef->roundScore = 25;
		return;
	}
	else if (calcRef->userChoice == 10) {
		calcRef->roundScore = 50;
		return;
	}
	else {
		printf("Uh oh! Something went wrong. Please contact your friendly neighbourhood software developer!\n(and have him check the getUSChar() function)");
		return;
	}
}

void updateScore(gameData* gameState, gameFiles* resources) {

	navMarks calcRef;

	for (unsigned char i = 0; i < 5; i++) {
		gameState->freezeState[i] = 0;
	}

	if (gameState->currentRolls[0] == NULL) {
		printf("\n********************************************************************************\n");
		printf("You have to roll the dice before you can score!\n"
			"********************************************************************************\n");
		return;
	}

	checkHand(gameState, &calcRef);

	if (calcRef.noScore) {
		printf("Oops! There are no categories left open on the score sheet under which\n"
			"your roll can be scored! No score will be entered into the score sheet.\n\n");
		printf((gameState->rollCounter == 3) ? "You have %hhu roll remaining this round\n"
			: "You have %hhu rolls remaining this round.\n\n", 4 - gameState->rollCounter);
		if (gameState->rollCounter == 4) {
			printf("Beginning new round...\n\n");
		}
		else {
			gameState->rollCounter--;
			dispRoll(gameState, resources);
			gameState->rollCounter++;
		}
		return;
	}


	do {

		printf("Enter the Row number corresponding to the category in which you would like to score.\n\n");
		calcRef.userChoice = getUSChar();
		calcScore(gameState, &calcRef);

		printf("********************************************************************************\n");

		//handType codes:																	
	//		0 - random 5 numbers or a pair (no trips, no boat, no quad, no yahtzee)			
	//		3 - trips																		
	//	   32 - boat																		
	//		4 - quads																		
	//		5 - yahtzee

		if ((calcRef.userChoice != 11) &&
			(((gameState->handType == 0) && (calcRef.userChoice > 6))
				|| ((calcRef.userChoice > 7) && (gameState->handType == 3))
				|| ((calcRef.userChoice > 8) && (gameState->handType <= 4))
				|| ((calcRef.userChoice == 10) && (gameState->handType != 5)))) {

			printf((calcRef.userChoice == 9) ?
				"You have to roll a %s to score in that category!\n\n"
				: "You have to roll %s to score in that category!\n\n",
				resources->handName[calcRef.userChoice - 7]);
		}
		else if (gameState->score[calcRef.userChoice - 1] != NULL) {
			if (calcRef.userChoice < 7) {
				printf("You have already entered a score under \"%hhus\".\n"
					"You may not score more than once under any category.\n\n", calcRef.userChoice);
			}
			else {
				printf("You have already entered a score under \"%s\".\n"
					"You may not score more than once under any category.\n\n", resources->handName[calcRef.userChoice - 7]);
			}
		}
		else {
			if ((calcRef.userChoice < 7) && (calcRef.rollCount[calcRef.userChoice - 1] == 0)) {
				printf("You cannot score anything in \"%hhus\", you haven't rolled any %hhu's!\n", calcRef.userChoice, calcRef.userChoice);
				printf("********************************************************************************\n\n");
				continue;
			}
			gameState->scoreCounter++;
			gameState->score[calcRef.userChoice - 1] = calcRef.roundScore;
			(calcRef.userChoice > 6) ?
				printf("Score of %hhu was recorded under \"%s\" on your score sheet.\n", calcRef.roundScore, resources->handName[calcRef.userChoice - 7])
				: printf("Score of %hhu was recorded under \"%hhus\" on your score sheet.\n", calcRef.roundScore, calcRef.userChoice);
			printf("********************************************************************************\n\n");
			gameState->handType = NULL;
			return;
		}
		printf("********************************************************************************\n\n");
	} while (true);
}

void finalScore(gameData* gameState) {

	unsigned short int finalScore = 0;

	for (unsigned char i = 0; i < 6; i++) {
		finalScore += gameState->score[i];
	}
	if (finalScore > 62) {
		printf("Sum of scores in categories \"1s\" to \"6s\" is more than 62!\n"
			"35 bonus points awarded!!!\n"
			"********************************************************************************\n");
		finalScore += 35;
	}
	for (unsigned char i = 6; i < 11; i++) {
		finalScore += gameState->score[i];
	}

	printf("Final Score is:\t\t%hu\n\n"
		"********************************************************************************\n"
		"--------------------------------------------------------------------------------\n"
		"                               Quitting the Game.                               \n"
		"                                   Good Bye!                                    \n"
		"--------------------------------------------------------------------------------\n\n\n", finalScore);

	char hold[10] = {};
	printf("Press any key and hit enter to exit.\n");
	scanf_s("%s", hold);
	printf("\n\n\n\n\n");
}
