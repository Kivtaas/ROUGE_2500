#ifndef __BHAYANAS__CURSE_FUNCTIONS_H__
#define __BHAYANAS__CURSE_FUNCTIONS_H__


#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include "Structs.h"

/*
roomData *readFile

This functions opens the file and assigns all the coordinates
to the appropiate location in the struct.	

IN: File through argv[1]

OUT: pointer of roomData type

POST: roomData is filled with the appropiate information for each room. 
*/

roomData *readFile(char file[], int *x, int *y, int *floor, int *eCount) ;


/*
void initCurses

This functions initiates ncurses, calling all the appopiate methods in
	

IN: File through argv[1]

OUT: pointer of roomData type

POST: roomData is filled with the appropiate information for each room. 
*/
void initCurses() ;


/*
enemyStruct printRooms

This function prints out the rooms

IN: the roomData struct poiner

POST: Rooms are printed out.
*/
enemyStruct *printRooms(roomData *rooms, int eCount);


/*
void addItems

This function puts all the items in a room in their appropiate location in the room.	

IN: the roomData struct for the current room and the current room number.
 
OUT: Pointer to the portion of the stack where enemy data is stored

POST: Rooms are filled with their appropiate items.
*/
void addItems(roomData room, int roomNum, int *mCount, enemyStruct *enemies);


/*
void moveEnemies

This function cycles through the enemies and moves them appropiately 
according to their movement pattern. The function also calls the 
attack function if contact with the player is made.	

IN: enemyStruct for enemies, amount of enemies, player struct

POST: Enemies in their new location
*/

void moveEnemies(enemyStruct *enemies, int count, playerInfo *user);


/*
void endGame

This functions ends the game and prints out the players gold and potions amount. 	
The function also frees the allocated memory of the roomData pointer

IN: the amount of gold and potions and roomData pointer


POST: Game ends, player gold and potions is printed, and roomData pointer is freed. 
*/
void endGame(int gold, int potions, roomData *rooms, itemData *items, int itemCount);


/*
void updateNoti

This function updates the notification at the top of the screen	

IN: The notification ID

POST: The notification is updated.
*/

void updateNoti(int status);


/*
void gameloop

This function is a loop that allows the player to move and runs the game.

POST: Game is played
*/
void gameLoop(int y, int x, int floor, roomData *rooms, enemyStruct *enemies, int eNum);


/*
void addEnemy

This function adds the enemy to the enemyStruct and fills the enemy
with the appropiate data. (Health, etc)

IN: Type of enemy, x postion, y position, room, and enemyStruct pointer

POST: enemy information is stored and ready to be used.
*/
void addEnemy(char type, int x, int y, int room, enemyStruct *enemy);

/*
void attack

This function allows the enemy and the player to attack each other.

IN: The playerinfo pointer, the enemy pointer, and the y and x position of the enemy,

POST: Player and enemy engage in an epic fight. Stats are updated accordingly
*/
void attack(playerInfo *player, enemyStruct *enemy, int y, int x);


/*
void generateHallways

This function connects all the doors together so that the player can go between
rooms and won't teleport from door to door.

IN: The roomdata pointer

POST: Hallways are generated so the player can walk.
*/
void generateHallways(roomData *rooms);


/*
void addEquip

This function stores the equipment that the player picks up so that it can be 
displayed later on

IN: The items pointer, the current amount of items, and the type of item.

POST: Equipment information is stored properly to be accessed later.
*/
void addEquip(itemData *items, int *itemCount, char type);



#endif /*CurseFunctions.h*/
