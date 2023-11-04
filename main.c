/*
Copyright© Spencer Hiscox, 2023
All Rights Reserved
*/


#include "prototypes.h"

int main() {

	gameFiles resources;
	gameData gameState;
	bool quit = false;
	unsigned char preScore;
	char userChoice[6] = {};

	printf("********************************************************************************\n");
	printf("*********************************** Rollzee ************************************\n");
	printf("********************************************************************************\n\n");

	getPlayerName(&gameState);
	dispWelcome(&gameState);

	do {
		do {
			bool crazyFail = false;
			do {
				if (!crazyFail) {
					crazyFail = true;
					printf("\n\nDo you want to roll, score or quit?\n\nEnter (roll / score / quit): ");
				}
				else {
					printf("\n\nI'm sorry, you must enter either 'roll' or 'score' or 'quit'. No other entry will be accepted.\nNOTE: The field is case-sensitive.\n"
						"\nDo you want to roll, score or quit?\n\n Enter (roll / score / quit): ");
				}
				scanf_s("%s", userChoice, 6);
			} while ((strcmp(userChoice, "score")) && (strcmp(userChoice, "roll")) && (strcmp(userChoice, "quit")));

			if (!strcmp(userChoice, "roll")) {
				if (gameState.rollCounter != 1) {
					freezeDie(&gameState);
				}
				rollDie(&gameState);
				dispRoll(&gameState, &resources);
				gameState.rollCounter++;
			}
			else if (!strcmp(userChoice, "score")) {
				if (gameState.currentRolls[0] != NULL) {
					dispScore(&gameState, quit);
				}
				preScore = gameState.scoreCounter;
				updateScore(&gameState, &resources);
				if (preScore != gameState.scoreCounter) {
					dispScore(&gameState, quit);
					gameState.rollCounter == 4;
				}
			}
			else if (!strcmp(userChoice, "quit")) {
				quit = true;
				break;
			}
			if (gameState.scoreCounter == gameState.roundCounter) {
				break;
			}
		} while ((gameState.rollCounter <= 3) && (!quit));

		if ((!quit) && (gameState.scoreCounter != gameState.roundCounter)) {
			printf("You have reached the maximum number of rolls in a single round (3).\n"
				"Proceeding to score sheet...\n");
			dispScore(&gameState, quit);
			preScore = gameState.scoreCounter;
			updateScore(&gameState, &resources);
			if ((gameState.roundCounter < 11) && (gameState.scoreCounter != preScore)) {
				dispScore(&gameState, quit);
			}
			else if ((preScore == gameState.scoreCounter) && (gameState.rollCounter > 3)) {
				gameState.scoreCounter++;
			}
		}
		if ((gameState.roundCounter == 11) || (quit)) {
			if ((!quit) && (gameState.roundCounter == 11)) {
				printf("You have reached the maximum number of rounds allowable in a game (11).");
			}
			dispScore(&gameState, quit);
			finalScore(&gameState);
			return 0;
		}
		if ((gameState.rollCounter > 3) || (gameState.scoreCounter == gameState.roundCounter)){
			gameState.roundCounter++;
			gameState.rollCounter = 1;
		}

	} while ((gameState.roundCounter != 12) && (!quit));
}
