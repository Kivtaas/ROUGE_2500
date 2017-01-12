/***********************************Curse_functions.c*************************
Name: Saatvik Bhayana                                     id: 0939774
Submission date: Sunday 13th                              course: CIS_2500
******************************************************************************/

#include "Curse_functions.h"

roomData *readFile(char file[], int *x, int *y, int *floor, int *eCount) {

	FILE *fp1;

	fp1 = fopen(file, "r");

	if (fp1 == NULL) {
		printf("File not found, Exiting\n");
		exit(1);
	}

	roomData *rooms = malloc(6 * sizeof(roomData));  //allocates 6 "room sizes".

	char* c;
	char text[150];

	int counter = 0;
	int enemyCounter = 0;

	do {
		c = fgets(text, 150, fp1);
		if (c != NULL) {
			char temp[10];
			int roomCount = 0;
			
			if(counter!= 5)
			text[strlen(text) - 1] = ' ';		//sets the last character as a space to know when to end copy
			else
			text[strlen(text)] = ' ';	
			
			for (int i = 0; i < strlen(text); i++) {

				if (text[i] == 'X') {			//checks if the character at i is an X (for room dimensions)

					for (int j = 0; text[j] != 'X'; j++) {  //for loop to copy before the X

						temp[j] = text[j];

					}
					temp[i] = '\0';
					rooms[counter].walls[0][0] = atoi(temp);

					for (int j = 0; text[i] != ' '; j++) {	//for loop to copy after the X

						temp[j] = text[i + 1];
						i++;

					}

					temp[i] = '\0';

					rooms[counter].walls[0][1] = atoi(temp);

				}

				else if (text[i] == 'd') {		//checks if char is a d, for door.
					i++;
					switch (text[i]) { //checks which wall the door is on and assigns the variable appropiately

					case 'n':
						rooms[counter].doors[roomCount][0] = 1;
						for (int j = 0; text[i] != ' '; j++) {

							temp[j] = text[i + 1];
							i++;

						}
						temp[strlen(temp) - 1] = '\0';
						rooms[counter].doors[roomCount][1] = atoi(temp);

						break;

					case 'e':
						rooms[counter].doors[roomCount][0] = 2;
						for (int j = 0; text[i] != ' '; j++) {

							temp[j] = text[i + 1];
							i++;

						}
						temp[strlen(temp) - 1] = '\0';
						rooms[counter].doors[roomCount][1] = atoi(temp);
						break;

					case 's':
						rooms[counter].doors[roomCount][0] = 3;
						for (int j = 0; text[i] != ' '; j++) {

							temp[j] = text[i + 1];
							i++;

						}
						temp[strlen(temp) - 1] = '\0';
						rooms[counter].doors[roomCount][1] = atoi(temp);
						break;

					case 'w':
						rooms[counter].doors[roomCount][0] = 4;
						for (int j = 0; text[i] != ' '; j++) {

							temp[j] = text[i + 1];
							i++;

						}
						temp[strlen(temp) - 1] = '\0';
						rooms[counter].doors[roomCount][1] = atoi(temp);
						break;

					}

					roomCount++;

				}

				else if ((text[i] == 'h' || text[i] == 'g' || text[i] == 'G'	//checks if the item is any other item (to avoid reading in numbers)
						|| text[i] == 'w' || text[i] == 'W' || text[i] == 'e'	// aswell as avoid a segfault
						|| text[i] == 'm' || text[i] == 'M' || text[i] == 'p'
						|| text[i] == 'z' || text[i] == 'a')
						&& text[i - 1] != 'd') {
					switch (text[i]) {										//assigns a variable a certain value according to which item it is

					case 'h':
						rooms[counter].data[rooms[counter].elementCount][0] = 1;
						break;
					case 'a':
						rooms[counter].data[rooms[counter].elementCount][0] = 2;
						break;
					case 'z':
						rooms[counter].data[rooms[counter].elementCount][0] = 3;
						break;
					case 'g':
						rooms[counter].data[rooms[counter].elementCount][0] = 4;
						break;
					case 'G':
						rooms[counter].data[rooms[counter].elementCount][0] = 5;
						break;
					case 'w':
						rooms[counter].data[rooms[counter].elementCount][0] = 6;
						break;
					case 'W':
						rooms[counter].data[rooms[counter].elementCount][0] = 7;
						break;
					case 'm':
						rooms[counter].data[rooms[counter].elementCount][0] = 8;
						enemyCounter ++;
						break;
					case 'e':
						rooms[counter].data[rooms[counter].elementCount][0] = 9;
						break;
					case 'M':
						rooms[counter].data[rooms[counter].elementCount][0] = 10;
						enemyCounter ++;
						break;
					case 'p':
						rooms[counter].data[rooms[counter].elementCount][0] = 11;
						break;
					}

					for (int j = 0; text[i] != ','; j++) {

						temp[j] = text[i + 1];
						i++;

					}

					temp[strlen(temp) - 1] = '\0';

					rooms[counter].data[rooms[counter].elementCount][1] = atoi(
							temp);

					for (int j = 0; text[i] != ' '; j++) {

						temp[j] = text[i + 1];
						i++;

					}

					temp[strlen(temp) - 1] = '\0';

					rooms[counter].data[rooms[counter].elementCount][2] = atoi(
							temp);

					if (rooms[counter].data[rooms[counter].elementCount][0] == 1) { //if the item is the hero, records the position and floor
						*x = rooms[counter].data[rooms[counter].elementCount][1];
						*y = rooms[counter].data[rooms[counter].elementCount][2];
						*floor = counter;
					}

					rooms[counter].elementCount++;

				}

			}

			counter++;

		}
	} while (c != NULL);

	fclose(fp1);

	*eCount = enemyCounter;


	return rooms;

}

void initCurses() {
	initscr();
	cbreak();
	noecho();
	curs_set(0);		//sets the cursor to be invisible
	keypad(stdscr, TRUE);
	move(0 , 2);
	printw("The player has started the game!");

}

enemyStruct *printRooms(roomData *rooms, int eCount) {


	enemyStruct *enemies = malloc((eCount) * sizeof(enemyStruct));


	int mCount = 0;

	for (int i = 0; i < 3; i++) {  //for loop for printing out the top 3 rooms

		int y = rooms[i].walls[0][0], x = rooms[i].walls[0][1];

		move(4, 3 + (i * (28)));
		vline('|', y);
		move(4, x + 4 + (i * (28)));
		vline('|', y);

		move(3, 3 + (i * (28)));
		hline('-', x + 2);
		move(4 + y, 3 + (i * (28)));
		hline('-', x + 2);

		for (int j = 0; j < y; j++) {
			move(j + 4, 4 + (i * 28));
			hline('.', x);
		}

		addItems(rooms[i], i, &mCount, enemies);  //calls method to add items

		for (int j = 0; j < 4; j++) {  //for loop for doors

			if (rooms[i].doors[j][0] != 0) {

				if (rooms[i].doors[j][0] == 1) {
					move(3, rooms[i].doors[j][1] + 3 + (i * 28));
					addch('+');
				}

				if (rooms[i].doors[j][0] == 2) {
					move(rooms[i].doors[j][1] + 3, x + 4 + (i * 28));
					addch('+');
				}

				if (rooms[i].doors[j][0] == 3) {
					move(y + 4, rooms[i].doors[j][1] + 3 + (i * 28));
					addch('+');
				}

				if (rooms[i].doors[j][0] == 4) {
					move(rooms[i].doors[j][1] + 3, 3 + (i * 28));
					addch('+');
				}

			}

		}

	}

	for (int i = 0; i < 3; i++) {	//for loops for the bottom 3 rooms

		int y = rooms[i + 3].walls[0][0], x = rooms[i + 3].walls[0][1];

		move(4 + (23), 3 + (i * (28)));
		vline('|', y);
		move(4 + (23), x + 4 + (i * (28)));
		vline('|', y);

		move(3 + (23), 3 + (i * (28)));
		hline('-', x + 2);
		move(4 + (23 + y), 3 + (i * (28)));
		hline('-', x + 2);

		for (int j = 0; j < y; ++j) {
			move(j + 27, 4 + (i * 28));
			hline('.', x);
		}

		addItems(rooms[i + 3], i + 3, &mCount, enemies);

		for (int j = 0; j < 4; j++) {

			if (rooms[i + 3].doors[j][0] != 0) {

				if (rooms[i + 3].doors[j][0] == 1) {
					move(26, rooms[i + 3].doors[j][1] + 3 + (i * 28));
					addch('+');
				}

				if (rooms[i + 3].doors[j][0] == 2) {
					move(rooms[i + 3].doors[j][1] + 26, x + 4 + (i * 28));
					addch('+');
				}

				if (rooms[i + 3].doors[j][0] == 3) {
					move(y + 27, rooms[i + 3].doors[j][1] + 3 + (i * 28));
					addch('+');
				}

				if (rooms[i + 3].doors[j][0] == 4) {
					move(rooms[i + 3].doors[j][1] + 26, 3 + (i * 28));
					addch('+');
				}

			}

		}

	}

	generateHallways(rooms);
	return enemies;
}

void addItems(roomData room, int roomNum, int *mCount, enemyStruct *enemies) {


	int monster = 0;  //int for which monster will spawn

	for(int i = 0; i < room.elementCount; i++) {

		char item;

		int x = room.data[i][2], y = room.data[i][1];

		switch (room.data[i][0]) {  //checks which item is to be placed and sets item as the symbol

		case 1:
			item = '@';
			break;

		case 2:
			item = '>';
			break;

		case 3:
			item = '<';
			break;

		case 4:
			item = '*';
			break;

		case 5:
			item = '8';
			break;

		case 6:
			item = ')';
			break;

		case 7:
			item = '(';
			break;

		case 8:

			monster = rand() % 4; //sets monster as a value between 0-3
			if(monster == 0) {
				item = 'A';
			}
			else if(monster == 1) {
				item = 'B';
			}
			else if(monster == 2) {
				item = 'S';
			}
			else if(monster == 3) {
				item = 'Z';
			}


			addEnemy(item, x, y, roomNum, &enemies[*mCount]);

			*mCount = *mCount+1;

			break;

		case 9:
			item = ']';
			break;

		case 10:
			item = 'T';
			addEnemy(item, x, y, roomNum, &enemies[*mCount]);
			*mCount = *mCount+1;
			break;

		case 11:
			item = '!';
			break;
		}

		if (roomNum < 3) { //adds the item to the appropiate position
			move(3 + y, 3 + (roomNum * (28)) + x);
			addch(item);
		} else {
			move(3 + (23) + y, 3 + ((roomNum - 3) * (28)) + x);
			addch(item);
		}

	}

}

void moveEnemies(enemyStruct *enemies, int count, playerInfo *user){

	for(int i = 0; i < count + 1; i++){

		if(enemies[i].health > 0){

			int oldX, oldY;

			oldY = enemies[i].location[0];

			oldX = enemies[i].location[1];


			if(enemies[i].type == 2){

				int num = rand()%4 + 1;

				if(num == 1 && ( mvinch(oldY, oldX + 1) == '.')){
					move(enemies[i].location[0], enemies[i].location[1] += 1);
					addch('B');
					move(oldY, oldX);
					addch('.');
				}
				else if (num == 2 && mvinch(oldY, oldX - 1) == '.'){
					move(enemies[i].location[0], enemies[i].location[1] -= 1);
					addch('B');
					move(oldY, oldX);
					addch('.');
				}
				else if (num == 3 && mvinch(oldY + 1, oldX) == '.'){
					move(enemies[i].location[0]+= 1, enemies[i].location[1] );
					addch('B');
					move(oldY, oldX);
					addch('.');
				}
				else if (num == 4 && mvinch(oldY - 1, oldX) == '.'){
					move(enemies[i].location[0]-= 1, enemies[i].location[1] );
					addch('B');
					move(oldY, oldX);
					addch('.');
				}

				
				if(num == 1 && ( mvinch(oldY, oldX + 1) == '@')){
					attack(user, enemies, oldY, oldX);
				}
				else if (num == 2 && mvinch(oldY, oldX - 1) == '@'){
					attack(user, enemies, oldY, oldX);
				}
				else if (num == 3 && mvinch(oldY + 1, oldX) == '@'){
					attack(user, enemies, oldY, oldX);
				}
				else if (num == 4 && mvinch(oldY - 1, oldX) == '@'){
					attack(user, enemies, oldY, oldX);
				}


			}

			else if (enemies[i].type == 3){


				if((enemies[i].cycle == 1 || enemies[i].cycle == 2) && ((mvinch(oldY, oldX + 1) == '.') || (mvinch(oldY, oldX + 1) == '@'))) {

					if(mvinch(oldY, oldX + 1) == '.'){
						move(enemies[i].location[0], enemies[i].location[1] += 1);
						addch('S');
						move(oldY, oldX);
						addch('.');
					}
					else{
						if(mvinch(oldY, oldX + 1) == '@'){
							attack(user, enemies, oldY, oldX);
						}
					}
				}

				else if((enemies[i].cycle == 3 || enemies[i].cycle == 4) && ((mvinch(oldY, oldX -  1) == '.') || (mvinch(oldY, oldX - 1) == '@'))){

					if(mvinch(oldY, oldX - 1) == '.'){
						move(enemies[i].location[0], enemies[i].location[1] -= 1);
						addch('S');
						move(oldY, oldX);
						addch('.');
					}
					else if(mvinch(oldY, oldX - 1) == '@'){
							attack(user, enemies, oldY, oldX);

					}

				}

				if(enemies[i].cycle == 4)
					enemies[i].cycle = 1;
				else
					enemies[i].cycle = enemies[i].cycle + 1;
			}

			else if(enemies[i].type == 4){


				if(enemies[i].cycle == 1  && mvinch(oldY - 1, oldX) == '.'){
					move(enemies[i].location[0] -= 1, enemies[i].location[1]);
					addch('Z');
					move(oldY, oldX);
					addch('.');
					enemies[i].cycle = 2;
				}
				else if (enemies[i].cycle == 2 && mvinch(oldY + 1, oldX) == '.'){
					move(enemies[i].location[0]+= 1, enemies[i].location[1] );
					addch('Z');
					move(oldY, oldX);
					addch('.');
					enemies[i].cycle = 1;
				}
				
				else if(enemies[i].cycle == 1 && ( mvinch(oldY - 1, oldX ) == '@')){
					attack(user, enemies, oldY, oldX);
				}
				
				else if(enemies[i].cycle == 2 && ( mvinch(oldY + 1, oldX ) == '@')){
					attack(user, enemies, oldY, oldX);
				}
	
			}

			else if(enemies[i].type == 5){


				if(enemies[i].cycle == 2 && mvinch(oldY, oldX + 1) == '.'){
					move(enemies[i].location[0], enemies[i].location[1] += 1);
					addch('T');
					move(oldY, oldX);
					addch('.');
				}
				else if (enemies[i].cycle == 4 && mvinch(oldY, oldX - 1) == '.'){
					move(enemies[i].location[0], enemies[i].location[1] -= 1);
					addch('T');
					move(oldY, oldX);
					addch('.');
				}
				else if (enemies[i].cycle == 3 && mvinch(oldY + 1, oldX) == '.'){
					move(enemies[i].location[0]+= 1, enemies[i].location[1] );
					addch('T');
					move(oldY, oldX);
					addch('.');
				}
				else if (enemies[i].cycle == 1 && mvinch(oldY - 1, oldX) == '.'){
					move(enemies[i].location[0]-= 1, enemies[i].location[1] );
					addch('T');
					move(oldY, oldX);
					addch('.');
				}
				
				else if(enemies[i].cycle == 1 && ( mvinch(oldY - 1, oldX ) == '@')){
					attack(user, enemies, oldY, oldX);
				}
				
				else if(enemies[i].cycle == 2 && ( mvinch(oldY , oldX + 1 ) == '@')){
					attack(user, enemies, oldY, oldX);
				}
				
				else if(enemies[i].cycle == 3 && ( mvinch(oldY + 1, oldX) == '@')){
					attack(user, enemies, oldY, oldX);
				}
				
				else if(enemies[i].cycle == 4 && ( mvinch(oldY , oldX + 1) == '@')){
					attack(user, enemies, oldY, oldX);
				}
				

				if(enemies[i].cycle == 4)
					enemies[i].cycle = 1;
				else
					enemies[i].cycle = enemies[i].cycle + 1;


			}


		}
	}
}

void endGame(int gold, int potions, roomData *rooms, itemData *items, int itemCount) {
	endwin();		//stops ncurses
	system("clear");
	printf("Gold:  %d,  Potions:  %d  \n", gold, potions);
	free(rooms);	//frees the memory allocated for rooms
	
	for(int i = 0; i < itemCount; i++){
		
		switch(items[i].type){
			
			case 1:
				printf("Normal Weapon with %d attack. \n", items[i].stat);
				break;
			case 2:
				printf("Rare Weapon with %d attack. \n", items[i].stat);
				break;
			case 3:
				printf("Equipment with %d defence. \n", items[i].stat);
				break;
			
			
		}
	}
	
	free(items);
	
	exit(0);
}

void updateNoti(int status){

	switch(status){

	case 1:
		move(0,2);
		printw("Hero picked up some gold!");
		break;

	case 2:
		move(0,2);
		printw("Hero picked up a potion!");
		break;

	case 3:
		move(0,2);
		printw("Hero picked up a common Weapon");
		break;

	case 4:
		move(0,2);
		printw("Hero picked up a rare Weapon!");
		break;
	case 5:
		move(0,2);
		printw("Hero picked up some equipment");
		break;
	case 6:
		move(0,2);
		printw("Hero opened a door!");
		break;
	case 7:
		move(0,2);
		printw("Hero recoverd full health!");
		break;
	case 8:
		move(0,2);
		printw("Hero is out of pots!");
		break;
	case 9:
		move(0,2);
		printw("Hero stepped on a common weapon and broke it.");
		break;
	case 10:
		move(0,2);
		printw("Hero stepped on a rare weapon and broke it.");
		break;
	case 11:
		move(0,2);
		printw("Hero stepped on some eqiupment and broke it.");
		break;
	case 12:
		move(0,2);
		printw("Hero picked up a lot of gold.");
		break;

	}


}

void gameLoop(int y, int x, int floor, roomData *rooms, enemyStruct *enemies, int eNum) {

	playerInfo user;
	
	itemData *items = malloc(5 * sizeof(itemData));;


	user.health = 50;
	user.playerAttack = 5;
	user.potionCount = 1;
	user.gold = 0;
	
	int equipCount = 0;

	char temp = '.';

	if(floor < 3) {		//sets x and y as the appropiate starting amounts

		x = (x + 3 + (floor*28));
		y = y+3;
	}
	else {
		y = y+26;
		x = x + 3 +((floor - 3)*28);
	}

	move(y,x);

	while(1) { //starts the loop

		move(48 , 2);
		printw("Health: %d, Potions: %d, Attack: %d Inv:%d/5  ", user.health, user.potionCount, user.playerAttack, equipCount);


		char keyInput = getch();

		move (0, 0);
		clrtoeol();

		if(keyInput == 'w' ) {  //checks the key the user enters

			move(y-1,x);

			if(inch() != 'T' && inch()!= '-' && inch() != 'A' && inch() != 'Z' && inch() != 'S' && inch() != 'B' && inch() != ' ' && inch()!= '|') { //if the position to move to isn't blocked

				if(inch() == '!' || inch() == '*' || inch() == '(' || inch() == ')' || inch() == ']' || inch() == '8')	{
					move(y,x);																							//prints a dot
					addch('.');
					move(y-1,x);
					addEquip(items, &equipCount, inch());
				}
				else {
					move(y,x);																							
					addch(temp);
					move(y-1,x);
					temp = inch();
				}

				if(inch() == '!'){  //if the player steps on any collectable items.
					user.potionCount+=1;
					updateNoti(2);
				}
				if(inch() == '*'){
					updateNoti(1);
					user.gold+= rand() % 50;
				}
				if(inch() == '8'){
					user.gold+= (rand() % 200) + 50;
					updateNoti(12);
				}
				if(inch() == '+')
					updateNoti(6);
				if(inch() == '<' || inch() == '>')		//if steps on any stairs, calls to end the program
					endGame(user.gold, user.potionCount, rooms, items, equipCount);

				move(y-1, x);
				addch('@');
				move(y-=1,x);


			}


			 if(inch() == 'A' || inch() == 'B' || inch() == 'S' || inch() == 'Z' || inch() == 'T'){

				attack(&user, enemies, y-1, x);


				move(y-1, x);

				if(inch() == '.'){
					move(y,x);																							//prints a dot
					addch('.');
					move(y-1,x);
					addch('@');
					move(y-=1,x);

				}

			}


		}

		if(keyInput == 's' ) {  //same thing as above but with different direction
			move(y+1,x);

			if(inch() != 'T' && inch()!= '-' && inch() != 'A' && inch() != 'Z' && inch() != 'S' && inch() != 'B' && inch() != ' ' && inch()!= '|') { //if the position to move to isn't blocked

				if(inch() == '!' || inch() == '*' || inch() == '(' || inch() == ')' || inch() == ']' || inch() == '8'){
					move(y,x);																							//prints a dot
					addch('.');
					move(y+1,x);
					addEquip(items, &equipCount, inch());
				}
				else {
					move(y,x);																							//prints a dot
					addch(temp);
					move(y+1,x);
					temp = inch();
				}

				if(inch() == '!'){  //if the player steps on any collectable items.
					user.potionCount+=1;
					updateNoti(2);
				}
				if(inch() == '*'){
					updateNoti(1);
					user.gold+= rand() % 50;
				}
				if(inch() == '8'){
					user.gold+= (rand() % 200) + 50;
					updateNoti(12);
				}
				if(inch() == '+')
					updateNoti(6);
				if(inch() == '<' || inch() == '>')
					endGame(user.gold, user.potionCount, rooms, items, equipCount);

				move(y+1, x);
				addch('@');
				move(y+=1,x);

			}

			else if(inch() == 'A' || inch() == 'B' || inch() == 'S' || inch() == 'Z' || inch() == 'T'){

				attack(&user, enemies, y+1, x);

				move(y+1, x);

				if(inch() == '.'){
					move(y,x);																							//prints a dot
					addch('.');
					move(y+1,x);
					addch('@');
					move(y+=1,x);

				}

			}

		}

		if(keyInput == 'a' ) { //same thing as above but with different direction

			move(y,x-1);

			if(inch() != 'T' && inch()!= '|' && inch() != 'A' && inch() != 'Z' && inch() != 'S' && inch() != 'B'&& inch() != ' ' && inch()!= '-') {


				if(inch() == '!' || inch() == '*' || inch() == '(' || inch() == ')' || inch() == ']' || inch() == '8')	{
					
					move(y,x-1);
					addEquip(items, &equipCount, inch());
					move(y,x);																							//prints a dot
					addch('.');
					move(y,x-1);
				}
				else {
					move(y,x);																							//prints a dot
					addch(temp);
					move(y,x-1);
					temp = inch();
				}



				if(inch() == '!'){  //if the player steps on any collectable items.
					user.potionCount+=1;
					updateNoti(2);
					move(y,x-1);
				}
				if(inch() == '*'){
					updateNoti(1);
					user.gold+= rand() % 50;
					move(y,x-1);
				}
				if(inch() == '8'){
					user.gold+= (rand() % 200) + 50;
					updateNoti(12);
					move(y,x-1);
				}
				if(inch() == '+'){
					updateNoti(6);
					 move(y,x-1);
				}
				if(inch() == '<' || inch() == '>')
					endGame(user.gold, user.potionCount, rooms, items, equipCount);

				addch('@');
				move(y,x-=1);


			}


			else if(inch() == 'A' || inch() == 'B' || inch() == 'S' || inch() == 'Z' || inch() == 'T'){

				attack(&user, enemies, y, x-1);


				move(y, x-1);

				if(inch() == '.'){

					move(y,x);
					addch('.');
					move(y,x-1);
					addch('@');
					move(y,x-=1);

				}

			}

		}

		if(keyInput == 'd' ) { //same thing as above but with different direction

			move(y,x+1);

			if(inch() != 'T' && inch()!= '|' && inch() != 'A' && inch() != 'Z' && inch() != 'S' && inch() != 'B' && inch() != ' ' && inch()!= '-') {


				if(inch() == '!' || inch() == '*' || inch() == '(' || inch() == ')' || inch() == ']' || inch() == '8')	{
					
					move(y,x+1);
					addEquip(items, &equipCount, inch());
					move(y,x);																							//prints a dot
					addch('.');
					
				}
				else {
					move(y,x);																							//prints a dot
					addch(temp);
					move(y,x+1);
					temp = inch();
				}


				if(inch() == '!'){  //if the player steps on any collectable items.
					user.potionCount+=1;
					updateNoti(2);
					move(y,x+1);
				}
				if(inch() == '*'){
					updateNoti(1);
					user.gold+= rand() % 50;
					move(y,x+1);
				}
				if(inch() == '8'){
					user.gold+= (rand() % 200) + 50;
					updateNoti(12);
					move(y,x+1);
				}
				if(inch() == '+'){
					updateNoti(6);
					 move(y,x+1);
				}
				if(inch() == '<' || inch() == '>')
					endGame(user.gold, user.potionCount, rooms, items, equipCount);

				addch('@');
				move(y,x+=1);


			}



			else if(inch() == 'A' || inch() == 'B' || inch() == 'S' || inch() == 'Z' || inch() == 'T'){

				attack(&user, enemies, y, x+1);

				move(y, x+1);

				if(inch() == '.'){
					move(y,x);																							//prints a dot
					addch('.');
					move(y,x+1);
					addch('@');
					move(y,x+=1);

				}

			}

		}

		if(keyInput == 'q' || user.health <= 0) { //if the user enters q, quits the program
			endGame(user.gold, user.potionCount, rooms, items, equipCount);
		}
		
		if(keyInput == 'p'){
		
			if(user.potionCount != 0){
				user.health = 50;
				user.potionCount -= 1;
				updateNoti(7);
			}
			else{
				updateNoti(8);
			}
		}

		moveEnemies(enemies, eNum, &user);

	}
}

void addEnemy(char type, int x, int y, int room, enemyStruct *enemy){


	switch(type){

	case 'A':
		enemy->type = 1;
		enemy->speed = 2;
		enemy->attack = 1;
		enemy->health = 5;
		enemy->cycle = 1;
		break;

	case 'B':
		enemy->type = 2;
		enemy->speed = 4;
		enemy->attack = 1;
		enemy->health = 5;
		enemy->cycle = 1;
		break;

	case 'S':
		enemy->type = 3;
		enemy->speed = 4;
		enemy->attack = 1;
		enemy->health = 5;
		enemy->cycle = 1;
		break;

	case 'Z':
		enemy->type = 4;
		enemy->speed = 2;
		enemy->attack = 1;
		enemy->health = 5;
		enemy->cycle = 1;
		break;

	case 'T':
		enemy->type = 5;
		enemy->speed = 3;
		enemy->attack = 5;
		enemy->health = 50;
		enemy->cycle = 1;
		break;



	}

	if (room < 3) {
				enemy->location[0] = 3+y;
				enemy->location[1] = 3 + (room*28) + x;
	}
			else {
				enemy->location[0] = 3 + (23) + y;
				enemy->location[1] = 3 + ((room - 3) * (28)) + x;
			}
}

void attack(playerInfo *player, enemyStruct *enemy, int y, int x){

	int i = 0;

	while ((enemy[i].location[0] != y) || (enemy[i].location[1] != x)){
		i++;
	}
	
	if(((rand()%10) + 1 ) > enemy[i].speed){
		enemy[i].health	= enemy[i].health - player->playerAttack;
		move(0,2);
		printw("Hero dealt %d damage", player->playerAttack);
	}

	else{

		if(enemy[i].type == 1) {
		
			if(player->playerAttack > 1){
				player->playerAttack = player->playerAttack - 1;
				move(0,2);
				printw("Hero lost 1 attack!");
			}
		}
		else{
			player->health = player->health - enemy[i].attack;
			move(0,2);
			printw("Hero lost %d health", enemy[i].attack);
		}

	}

	if(enemy[i].health <= 0){

		mvaddch(enemy[i].location[0], enemy[i].location[1], '.');
		
		move (0, 0);
		clrtoeol();
		move(0,2);
		switch(enemy[i].type){

		case 1:
			printw("Hero killed A");
			break;

		case 2:
			printw("Hero killed B");
			break;

		case 3:
			printw("Hero killed S");
			break;

		case 4:
			printw("Hero killed Z");
			break;

		case 5:
			printw("Hero killed T");
			break;


		}


	}
}

void generateHallways(roomData *rooms) {

	for (int i = 0; i < 6; i++) {

		for (int j = 0; j < 4; j++) {

			if (rooms[i].doors[j][0] == 1) {

				if (i < 3) {

					move(2, rooms[i].doors[j][1] + 3 + (i * 28));
					addch('#');
					move(1, rooms[i].doors[j][1] + 3 + (i * 28));
					addch('#');

					if (i != 2) {

						for (int k = 0; k + rooms[i].doors[j][1] + 3 + (i * 28) < (((i + 1) * 28) + 2); k++) {

							move(1, rooms[i].doors[j][1] + 3 + (i * 28) + k);
							addch('#');

						}

						for (int k = 0; k < 4; k++) {

							if (rooms[i + 1].doors[k][0] == 1) {

								for (int l = 0; l < rooms[i + 1].doors[k][1] + 2; l++) {

									move(1, (28 * (i + 1)) + 1 + l);
									addch('#');

								}
							}

							if (rooms[i + 1].doors[k][0] == 2) {

								for (int l = 0; l < 28 ; l++) {

									move(1, (28 * (i+1) + l + 1));
									addch('#');

								}

								for (int l = 0; l < rooms[i + 1].doors[k][1] + 3; l++) {

									move(1 + l, (28 * (i + 2) + 1) );
									addch('#');

								}


							}

							if (rooms[i + 1].doors[k][0] == 3) {

								for (int l = 0; l < 24; l++) {

									move(1 + l, (28 * (i + 1) + 1) );
									addch('#');

								}

								for (int l = 0; l < rooms[i + 1].doors[k][1] + 3; l++) {

									move(24, (28 * (i + 1) + 1) + l);
									addch('#');

								}


							}

							if (rooms[i + 1].doors[k][0] == 4) {

								for (int l = 0; l < rooms[i + 1].doors[k][1] + 3; l++) {

									move(1 + l, (28 * (i + 1) + 1));
									addch('#');

								}

							}
							

						}
					}
					
					for (int k = 0; k < 4; k++){

								if ((i == 0 || i == 2) && rooms[i + 3].doors[k][0] != 0 ){

									for(int l = 0; l < rooms[i].doors[j][1] + 1; l++){

										move(1, rooms[i].doors[j][1] - l + 1 + (28 * (i) + 1));
										addch('#');

									}

									for (int l = 0; l < 24; l++) {

										move(1 + l, (28 * (i) + 1));
										addch('#');

									}
									
									

									if(rooms[i + 3].doors[k][0] == 4){

										for (int l = 0; l < rooms[i + 3].doors[k][1] + 2; l++) {

											move(25 + l, 1 + ((i* 28)));
											addch('#');

										}


									}
									if(rooms[i + 3].doors[k][0] == 1){

										for (int l = 0; l < rooms[i + 3].doors[k][1] + 2; l++) {

											move(24, 1 + ((i* 28)) + l);
											addch('#');

										}

									}
									
									if(rooms[i+3].doors[k][0] == 3){
										
										
										for (int l = 0; l < 22; l++) {

											move(25 + l, 1 + ((i* 28)));
											addch('#');

										}
										
										for (int l = 0; l < rooms[i+3].doors[k][1] + 3; l++){
											
											move(46, (i*28) + l + 1);
											addch('#');
										}
										
									}
									
									if(rooms[i+3].doors[k][0] == 2){
										
										for(int l = 0; l < 29; l++){
													
											move(24, 1 + (i)*28 + l);
											addch('#');
	
										}
										
										for (int l = 0; l < rooms[i + 3].doors[k][1] + 3; l++){
											
											move(24+l, ((i+1)*28 + 1));
											addch('#');
											
											
										}
										
										
									}
								}
	
					}

				}

				else {

					move(25, rooms[i].doors[j][1] + 3 + (i - 3) * 28);
					addch('#');
					move(24, rooms[i].doors[j][1] + 3 + (i - 3) * 28);
					addch('#');


					if (i != 5){
						for (int k = 0; k + rooms[i].doors[j][1] + 3 + ((i-3) * 28) < ((((i - 3) + 1) * 28) + 2); k++) {

							move(24, rooms[i].doors[j][1] + 3 + ((i - 3) * 28) + k);
							addch('#');

						}
					}
					for (int k = 0; k < 4; k++) {

						if (rooms[i + 1].doors[k][0] == 1) {

							for (int l = 0; l < rooms[i + 1].doors[k][1] + 2; l++) {

								move(24, (28 * ((i - 3) + 1) + 1 + l));
								addch('#');

							}
						}

						if (rooms[i + 1].doors[k][0] == 2) {

							for (int l = 0; l < 28; l++) {

								move(24, (28 * ((i-3) + 1)) + l + 1) ;
								addch('#');

							}

							for (int l = 0; l < rooms[i + 1].doors[k][1] + 3; l++) {

								move(24 + l, (28 * ((i-3) + 2) + 1) );
								addch('#');

							}


						}

						if (rooms[i + 1].doors[k][0] == 3) {

							for (int l = 0; l < rooms[i + 1].walls[0][0] + 5 ; l++) {

								move(24 + l, (28 * ((i-3) + 1) + 1) );
								addch('#');

							}

							for (int l = 0; l < rooms[i + 1].doors[k][1] + 3; l++) {

								move(24 + rooms[i + 1].walls[0][0] + 5 , (28 * ((i-3) + 1) + 1) + l);
								addch('#');

							}


						}

						if (rooms[i + 1].doors[k][0] == 4) {

							for (int l = 0; l < rooms[i + 1].doors[k][1] + 3; l++) {

								move(24 + l, (28 * ((i-3) + 1) + 1));
								addch('#');

							}

						}



					}

				}
				
				
			}

			else if (rooms[i].doors[j][0] == 2) {

				if (i < 3) {

					for(int k = 0; k + rooms[i].walls[0][1] + 5 + (i * 28) < (((i + 1) * 28) + 2); k++){

						move(rooms[i].doors[j][1] + 3, rooms[i].walls[0][1] + 5 + (i * 28) + k);
						addch('#');

					}


					for(int d = 0; d < 4; d++){

						if(i !=2){

							if (rooms[i + 1].doors[d][0] == 1) {

								for(int k = 0; (rooms[i].doors[j][1]+2 - k ) > 0; k++){

									move(rooms[i].doors[j][1]+2 - k, (1 +(i+1) * 28));
									addch('#');

								}

								for (int l = 0; l < rooms[i + 1].doors[d][1] + 2; l++) {

									move(1, (28 * (i + 1)) + 1 + l);
									addch('#');

								}


							}

							if (rooms[i + 1].doors[d][0] == 2) {

								for(int k = 0; (rooms[i].doors[j][1]+2 - k ) > 0; k++){

									move(rooms[i].doors[j][1]+2 - k, (1 +(i+1) * 28));
									addch('#');

								}

								for (int l = 0; l < 29; l++) {

									move(1, ((28*(i+1) + 1) + l));
									addch('#');

								}

								for (int l = 0; l < rooms[i + 1].doors[d][1] + 3; l++) {

									move(1 + l, (28 * (i + 2) + 1));
									addch('#');

								}


							}


							else if(rooms[i + 1].doors[d][0] == 4) {

								if (rooms[i + 1].doors[d][1] < rooms[i].doors[j][1]){

									for(int k = 0; (rooms[i].doors[j][1] + 3 - k) > rooms[i + 1].doors[d][1] + 3; k++){

										move(rooms[i].doors[j][1]+ 2 - k, (1 +(i+1) * 28));
										addch('#');

									}
								}

								else{

									for(int k = 0; (rooms[i].doors[j][1]+ 2 + k ) < rooms[i + 1].doors[d][1] + 3; k++){

										move((rooms[i].doors[j][1]+ 3) + k, (1 +(i+1) * 28));
										addch('#');

									}

								}

							}

							else if (rooms[i + 1].doors[d][0] == 3){

								for(int k = 0; (rooms[i].doors[j][1]+ 2 + k ) < 24; k++){

									move((rooms[i].doors[j][1]+ 3) + k, (1 +(i+1) * 28));
									addch('#');

								}

								for (int l = 0; l < rooms[i + 1].doors[d][1] + 2; l++) {

									move(24, (28 * (i + 1)) + 1 + l);
									addch('#');

								}


							}

						}
					}

					for (int k = 0; k < 4; k++){

								if ((i == 0 || i == 2) && rooms[i + 3].doors[k][0] != 0 ){
									

									if(rooms[i + 3].doors[k][0] == 4){

										for (int l = 0; l < (22 - rooms[i].doors[k][1]) ; l++) {

											move(3 + rooms[i].doors[k][1] + l, 1 + (((i+1)* 28)));
											addch('#');

										}
										
										for (int l = 0; l < 28 ; l++) {

											move(24, 1 + (((i+1)* 28) - l));
											addch('#');

										}
										
									for (int l = 0; l < (rooms[i].doors[j][1]) + rooms[i+3].doors[k][1] + 2; l++) {

											move(23 + rooms[i].doors[j][1]  + l, 1 + (((i)* 28)));
											addch('#');

										}


									}
						
									if(rooms[i + 3].doors[k][0] == 1){

										for (int l = 0; l < (21 - rooms[i].doors[j][1]); l++) {

											move( rooms[i].doors[j][1] + 4 + l, 1 + (((i+1)* 28)));
											addch('#');

										}

									}
									
									if(rooms[i + 3].doors[k][0] == 3){
										
										
									for (int l = 0; l < (44 - rooms[i].doors[k][1]) ; l++) {

											move(3 + rooms[i].doors[k][1] + l, 1 + (((i+1)* 28)));
											addch('#');

										}
										
									}
									
									if(rooms[i+3].doors[k][0] == 2){
										
										for (int l = 0; l < (21 - rooms[i].doors[j][1]) + rooms[i+3].doors[k][1] + 2; l++) {

											move( rooms[i].doors[j][1] + 4 + l, 1 + (((i+1)* 28)));
											addch('#');

										}
										
										
									}
								}
	
					}


				}

				else {

					for(int k = 0; k + rooms[i].walls[0][1] + 5 + ((i-3) * 28) < ((((i-3) + 1) * 28) + 2); k++){

						move(23 + rooms[i].doors[j][1] + 3, rooms[i].walls[0][1] + 5 + ((i-3) * 28) + k);
						addch('#');

					}


					for(int d = 0; d < 4; d++){

						if(i !=5){

							if (rooms[i + 1].doors[d][0] == 1) {

								for(int k = 0; (rooms[i].doors[j][1]+2 - k ) > 0; k++){

									move(23 + rooms[i].doors[j][1]+2 - k, (1 +((i-3) +1) * 28));
									addch('#');

								}

								for (int l = 0; l < rooms[i + 1].doors[d][1] + 2; l++) {

									move(24, (28 * ((i-3) + 1)) + 1 + l);
									addch('#');

								}


							}

							if (rooms[i + 1].doors[d][0] == 2) {

								for(int k = 0; (rooms[i].doors[j][1]+2 - k ) > 0; k++){

									move(23 + rooms[i].doors[j][1] + 3 - k, (1 +((i-3) + 1) * 28));
									addch('#');

								}

								for (int l = 0; l < 29; l++) {

									move(24, (28 * ((i-3) + 1) + 1) + l);
									addch('#');

								}

								for (int l = 0; l < rooms[i + 1].doors[d][1] + 3; l++) {

									move(23 + 1 + l, (28 * ((i-3) + 2) + 1));
									addch('#');

								}


							}


							else if(rooms[i + 1].doors[d][0] == 4) {

								if (rooms[i + 1].doors[d][1] < rooms[i].doors[j][1]){

									for(int k = 0; (rooms[i].doors[j][1] + 4 - k) > rooms[i + 1].doors[d][1] + 3; k++){

										move(23 + rooms[i].doors[j][1]+ 3 - k, (1 +((i-3) +1) * 28));
										addch('#');

									}
								}

								else{

									for(int k = 0; (rooms[i].doors[j][1]+ 2 + k ) < rooms[i + 1].doors[d][1] + 3; k++){

										move((23 + rooms[i].doors[j][1]+ 3) + k, (1 +((i-3) + 1) * 28));
										addch('#');

									}

								}

							}

							else if (rooms[i + 1].doors[d][0] == 3){

								for(int k = 0; (rooms[i].doors[j][1]+ 3 + k ) < 24; k++){

									move(23 + (rooms[i].doors[j][1]+ 3) + k, (1 +((i-3) + 1) * 28));
									addch('#');

								}

								for (int l = 0; l < rooms[i + 1].doors[d][1] + 2; l++) {

									move(23 + 23, (28 * ((i-3) + 1)) + 1 + l);
									addch('#');

								}


							}

						}
					}

				}

			}

			else if (rooms[i].doors[j][0] == 3) {

				if (i < 3) {

					for(int k = 0; k + rooms[i].walls[0][0] + 3 < 23; k++){

						move(k + rooms[i].walls[0][0] + 5, rooms[i].doors[j][1] + 3 + (i * 28));
						addch('#');

					}

					for(int k = 0; k + rooms[i].doors[j][1] + 3 + (i * 28)  < ((i+1) * 28) + 2; k++) {

						move(24, k + rooms[i].doors[j][1] + 3 + (i * 28));
						addch('#');

					}


					for (int d = 0; d < 4; d++){

						if(i != 2){

							if ( rooms[i + 1].doors[d][0] == 1){

								for(int k = 0; (24 - k ) > 0; k++){

									move(24 - k, (1 +(i+1) * 28));
									addch('#');

								}

								for (int l = 0; l < rooms[i + 1].doors[d][1] + 2; l++) {

									move(1, (28 * (i + 1)) + 1 + l);
									addch('#');

								}

							}

							if (rooms[i + 1].doors[d][0] == 2) {

								for (int l = 0; l + (28 * (i) + 2) < (28 * (i + 1)) + 2; l++) {

									move(24, (28 * (i + 1)) + 1 + l);
									addch('#');

								}

								for(int k = 0; (24 - k) - 3 > rooms[i + 1].doors[d][1]; k++){

									move(24 - k, (1 + (i+2) * 28));
									addch('#');

								}
								
								

							}

							if (rooms[i + 1].doors[d][0] == 3) {

								for (int l = 0; l + (28 * (i) + 2) < (28 * (i) + 2) + rooms[i+1].doors[d][1] + 2; l++) {

									move(24, (28 * (i + 1)) + 1 + l);
									addch('#');

								}
								
								
							}

							if (rooms[i + 1].doors[d][0] == 4) {

								for(int k = 0; (24 - k) - 2 > rooms[i + 1].doors[d][1]; k++){

									move(24 - k, (1 + (i+1) * 28));
									addch('#');

								}


							}
						}
					}
					
					for (int k = 0; k < 4; k++){

								if ((i == 0 || i == 2) && rooms[i + 3].doors[k][0] != 0 ){
									

									if(rooms[i + 3].doors[k][0] == 4){
										
										for (int l = 0; l < 28 ; l++) {

											move(24, 1 + (((i+1)* 28) - l));
											addch('#');

										}
										
									for (int l = 0; l < (rooms[i].doors[j][1]) + rooms[i+3].doors[k][1] + 2; l++) {

											move(23 + rooms[i].doors[j][1]  + l, 1 + (((i)* 28)));
											addch('#');

										}


									}
						
									
									if(rooms[i + 3].doors[k][0] == 3){
										
										
									for (int l = 0; l < (23) ; l++) {

											move(24 + l, 1 + (((i+1)* 28)));
											addch('#');

										}
										
									}
									
									if(rooms[i+3].doors[k][0] == 2){
										
										for (int l = 0; l < (rooms[i].doors[j][1]) + rooms[i+3].doors[k][1] + 1; l++) {

											move(23 + rooms[i].doors[j][1] + 1 + l, 1 + (((i+1)* 28)));
											addch('#');

										}
										
										
									}
								}
	
					}

				}

				else {

					for(int k = 0; k + rooms[i].walls[0][0] + 3 < 22; k++){

						move(23 + k + rooms[i].walls[0][0] + 5, rooms[i].doors[j][1] + 3 + ((i-3) * 28));
						addch('#');

					}

				if(i != 5){
					for(int k = 0; k + rooms[i].doors[j][1] + 3 + ((i-3) * 28)  < (((i-3)+1) * 28) + 2; k++) {

						move(24 + 22, k + rooms[i].doors[j][1] + 3 + ((i-3) * 28));
						addch('#');

					}


					for (int d = 0; d < 4; d++){



							if ( rooms[i + 1].doors[d][0] == 1){

								for(int k = 0; (23 - k ) > 0; k++){

									move(46 - k, (1 +((i-3) + 1) * 28));
									addch('#');

								}

								for (int l = 0; l < rooms[i + 1].doors[d][1] + 2; l++) {

									move(24, (28 * ((i-3) + 1)) + 1 + l);
									addch('#');

								}

							}

							if (rooms[i + 1].doors[d][0] == 2) {

								for (int l = 0; l + ((i-3 ) *28) < ((i-3) + 1) * 28; l++) {

									move(46, (28 * ((i-3) + 1)) + 1 + l);
									addch('#');

								}

								for(int k = 0; (24 - k) - 3 > rooms[i + 1].doors[d][1]; k++){

									move(46 - k, (1 + ((i-3)+2) * 28));
									addch('#');

								}

							}

							if (rooms[i + 1].doors[d][0] == 3) {

								for (int l = 0; l + (28 * (i-3) + 2) < (28 * (i-3) + 2) + rooms[i+1].doors[d][1] + 2; l++) {

									move(46, (28 * (i-3 + 1)) + 1 + l);
									addch('#');

								}
							}

							if (rooms[i + 1].doors[d][0] == 4) {

								for(int k = 0; (24 - k) - 2 > rooms[i + 1].doors[d][1] + 1; k++){

									move(46 - k, (1 + (i-3+1) * 28));
									addch('#');

								}


							}
						}
					}

				}

			}

			else if (rooms[i].doors[j][0] == 4) {

				if (i < 3) {
					move(rooms[i].doors[j][1] + 3, (28*i) + 2);
					addch('#');

					for(int d = 0; d < 4; d++){

						if (i != 2){

							if(rooms[i+1].doors[d][0] == 1){

								for(int k = 0; rooms[i].doors[d][1] + 3 - k > 0; k++){

									move(rooms[i].doors[d][1] + 3 - k, (28*i) + 1 );
									addch('#');

								}

								for (int l = 0; l + (28 * (i) + 2) < (28 * (i + 1) + 2) + rooms[i+1].doors[d][1] + 2; l++) {

									move(1, (28 * (i)) + 1 + l);
									addch('#');

								}


							}


							else if(rooms[i+1].doors[d][0] == 2){

								for(int k = 0; rooms[i].doors[d][1] + 3 - k > 0; k++){

									move(rooms[i].doors[d][1] + 3 - k, (28*i) + 1 );
									addch('#');

								}

								for(int k = 0; k  < 56; k++){

									move(1, ((i) * 28) + 1 + k);
									addch('#');

								}

								for (int l = 0; l < rooms[i + 1].doors[d][1] + 3; l++) {

									move(1 + l, (28 * (i + 2) + 1));
									addch('#');

								}


							}

							else if(rooms[i+1].doors[d][0] == 3){

								for(int k = 0; rooms[i].doors[d][1] + 3 - k > 0; k++){

									move(rooms[i].doors[d][1] + 3 - k, (28*i) + 1 );
									addch('#');

								}


								for (int l = 0; l + (i * 28) < ((i + 1) * 28) + 1; l++) {

									move(1, (28 * i) + 1 + l);
									addch('#');

								}

								for (int l = 0; l < 24; l++) {

									move(1 + l, (28 * (i + 1) + 1));
									addch('#');

								}

								for (int l = 0; l < rooms[i+1].doors[d][1] + 3; l++){

									move(24, (28* (i + 1)  + 1 + l));
									addch('#');
								}


							}

							else if(rooms[i+1].doors[d][0] == 4){

								for(int k = 0; rooms[i].doors[d][1] + 3 - k > 0; k++){

									move(rooms[i].doors[d][1] + 3 - k, (28*i) + 1 );
									addch('#');

								}


								for (int l = 0; l + (i * 28) < ((i + 1) * 28) + 1; l++) {

									move(1, (28 * i) + 1 + l);
									addch('#');

								}

								for (int l = 0; l < rooms[i + 1].doors[d][1] + 3; l++) {

									move(1 + l, (28 * (i + 1) + 1));
									addch('#');



								}

							}

						}

					}
					
					for (int k = 0; k < 4; k++){

								if ((i == 0 || i == 2) && rooms[i + 3].doors[k][0] != 0 ){
									
									for(int l = 0; l < 24 - rooms[i].doors[k][1] - 2; l++){
										
										move(rooms[i].doors[k][1] + l + 3, (i * 28) + 1);
										addch('#');
									}
									
									
									if(rooms[i + 3].doors[k][0] == 4){

									
									for (int l = 0; l < (rooms[i].doors[j][1]) + rooms[i+3].doors[k][1] + 2; l++) {

											move(23 + rooms[i].doors[j][1]  + l, 1 + (((i)* 28)));
											addch('#');

										}


									}
						
									if(rooms[i + 3].doors[k][0] == 1){

										for(int l = 0; l < 28; l++){
											
											move(24, (i*28) + l + 1);
											addch('#');
											
											
										}

									}
									
									if(rooms[i + 3].doors[k][0] == 3){
										
										
									for (int l = 0; l < (44 - rooms[i].doors[k][1]) ; l++) {

											move(3 + rooms[i].doors[k][1] + l, 1 + (((i)* 28)));
											addch('#');

										}
										
									for (int l = 0; l < 28; l++){
											
											move(46, (i*28) + l + 1);
											addch('#');
											
											
										}	
										
									}
									
									if(rooms[i+3].doors[k][0] == 2){
										
										for(int l = 0; l < 28; l++){
											
											move(24, (i*28) + l + 1);
											addch('#');
											
											
										}
										
										for (int l = 0; l < 22 - rooms[i].doors[j][1];  l++) {

											move( 24 + l, 1 + (((i+1)* 28)));
											addch('#');

										}
										
										
									}
								}
	
					}

					
				}

				else {

					move(23 + rooms[i].doors[j][1] + 3, (28*(i-3)) + 2);
					addch('#');

					for(int d = 0; d < 4; d++){

						if (i != 5){

							if(rooms[i+1].doors[d][0] == 1){

								for(int k = 0; rooms[i].doors[d][1] + 3 - k > 0; k++){

									move(23 + rooms[i].doors[d][1] + 3 - k, (28*(i-3)) + 1 );
									addch('#');

								}

								for (int l = 0; l + (28 * (i) + 2) < (28 * (i + 1) + 2) + rooms[i+1].doors[d][1] + 2; l++) {

									move(24 , (28 * (i-3)) + 1 + l);
									addch('#');

								}


							}


							else if(rooms[i+1].doors[d][0] == 2){

								for(int k = 0; rooms[i].doors[d][1] + 3 - k > 0; k++){

									move(23 +  rooms[i].doors[d][1] + 3 - k, (28*(i-3)) + 1 );
									addch('#');

								}

								for(int k = 0; k  < 28 * ((i-3) + 1) + 1; k++){

									move(23 + 1, ((i-3) * 28) + 1 + k);
									addch('#');

								}

								for (int l = 0; l < rooms[i + 1].doors[d][1] + 3; l++) {

									move(23 + 1 + l, (28 * ((i-3) + 2) + 1));
									addch('#');

								}


							}

							else if(rooms[i+1].doors[d][0] == 3){

								for(int k = 0; rooms[i].doors[d][1] + 3 - k > 0; k++){

									move(23 + rooms[i].doors[d][1] + 3 - k, (28*(i-3)) + 1 );
									addch('#');

								}


								for (int l = 0; l + ((i - 3) * 28) < (((i - 3) + 1) * 28) + 1; l++) {

									move(24, (28 * (i - 3)) + 1 + l);
									addch('#');

								}

								for (int l = 0; l < 23; l++) {

									move(23 + 1 + l, (28 * ((i-3) + 1) + 1));
									addch('#');

								}

								for (int l = 0; l < rooms[i+1].doors[d][1] + 3; l++){

									move(24 + 22, (28* ((i-3) + 1)  + 1 + l));
									addch('#');
								}




							}

							else if(rooms[i+1].doors[d][0] == 4){

								for(int k = 0; rooms[i].doors[d][1] + 3 - k > 0; k++){

									move(rooms[i].doors[d][1] + 3 - k + 23, (28*(i-3)) + 1 );
									addch('#');

								}


								for (int l = 0; l + (i * 28) < ((i + 1) * 28) + 1; l++) {

									move(24, (28 * (i-3)) + 1 + l);
									addch('#');

								}

								for (int l = 0; l < rooms[i + 1].doors[d][1] + 2; l++) {

									move(1 + l + 24, (28 * ((i-3) + 1) + 1));
									addch('#');


								}

							}

						}

					}
				}



			}

		}

	}
}

void addEquip(itemData *items, int *itemCount, char type){
	
	if(*itemCount < 5){
			
		switch (type){
			
			case ')':
				
				items[*itemCount].type = 1;
				items[*itemCount].stat = rand()%9 + 1;
				updateNoti(3);
				*itemCount += 1;
				break;
				
			case '(':
			
				items[*itemCount].type = 2;
				items[*itemCount].stat = rand()%5 + 10;
				updateNoti(4);
				*itemCount += 1;
				break;
				
			case ']':
			
				items[*itemCount].type = 3;
				items[*itemCount].stat = rand()%9 + 1;
				updateNoti(5);
				*itemCount += 1;
				break;
		}
		
	}
	
	else{
			
		switch (type){
			
			case ')':
				
				updateNoti(9);
				
				break;
				
			case '(':
			
				updateNoti(10);
			
				break;
				
			case ']':
			
				updateNoti(11);
				
				break;
		}
		
	}
	

}




 