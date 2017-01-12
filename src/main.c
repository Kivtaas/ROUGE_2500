/********************main.c**********************
 Name: Saatvik Bhayana            id: 0939774
 Submission date: March 13th      course: CIS_2500
**************************************************/

#include <stdio.h>
#include "Curse_functions.h"


/*Function main
 *
 * This is the function that recieves the level file throuh argv, and calls the other functions.
 * This function also creates the variales that are passed throughout functions.
 *
 * IN: Level file through argv[1]
 * OUT: returns 0 if the program runs successfully
 * POST: The game runs and ends, and the amount of gold the user picked up is displayed.
 */

int main(int argc, char* argv[]) {

	roomData *ptr;
	enemyStruct *ePtr;

	int playerX = 0, playerY = 0, floor = 0, eCount = 0;


	srand (time(NULL));	//sets the random seed as the current time

	ptr = readFile(argv[1], &playerX, &playerY, &floor, &eCount);

	initCurses();

	ePtr = printRooms(ptr, eCount);

	gameLoop(playerX, playerY, floor, ptr, ePtr, eCount);

	return 0;

}
