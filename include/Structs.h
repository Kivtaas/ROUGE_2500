#ifndef BHAYANAS__STRUCTS_H__
#define BHAYANAS__STRUCTS_H__


/*
struct playerInfo:
This is a structure that holds all the information for the player including
The location the player starts (room, y, and x)
The amount of potions the player has
The health of the player (to be used later on)
The amount of gold the player has
*/

typedef struct {

	int location[1][3];
	int playerAttack;
	int potionCount;
	int health;
	int gold;

} playerInfo;

/*
struct roomData:
This is a structure that holds all the information for the rooms including
the Items in data, with [x][0] being which item it is, and [x][1] [x][2] being the y and x
The dimensions of the walls
The location of the doors
*/
typedef struct {

	int data[10][3];
	int walls[1][2];
	int doors[4][2];
	int elementCount;

} roomData;

/*
struct enemyStruct:
This struct holds all the data for the enemies
including their health, attack, speed, type and cycle number.
it also includes their current x and y positions.
*/
typedef struct {

	int health;
	int attack;
	int speed;
	int type;
	int cycle;
	int location[2];


}enemyStruct;


/*
struct itemData:
This struct holds the information for the items that the player picks up
This includes the type of item it is and the stat that the item gives
*/
typedef struct {

	int type;
	int stat;

}itemData;

#endif /*Structs.h*/
