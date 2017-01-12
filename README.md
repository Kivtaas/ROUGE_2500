/***********************************README************************************


/**********************************COMPILING**********************************/
To complie the program, run the command "make" which runs the makeFile.
The makeFile contains the following line:

gcc -Wall -std=c99 src/main.c src/Curse_functions.c -Iinclude -lncurses -o bin/runMe

The program complies with all warnings as well as in c99 mode.


/**********************************RUNNING************************************/
To run the program, navigate to the "bin" folder and execute "runMe" with the 
following command, replacing anything inbetween <> with the proper file path:
"./runMe <levelfile>"
or alternatively type:
"./bin/runMe  <levelfile>

/**********************************USAGE**************************************/
The program takes in 1 file, read through argv. Reads through the file and
then prints out a room with the specifications given in the file. After reading
and printing out the room, a game similar to Rogue is started and played until
either the player reaches the stairs, the player dies or the player hits 'q'.

Combat is started when a player or an enemy try to walk onto a space occupied by 
the other. The damage taken/given is displayed in a notification at the top
of the screen during gameplay.

Potions can now be drunk by hitting the "p" key, which recovers the hero to full
health (50).

Items are stored and printed out along with the gold at the end of the game.



Controls:
w: move up
a: move left
s: move down
d: move right
q: quit game.
p: drink potion

/*****************************KNOWN LIMITATIONS********************************/
- The program only takes in 10 items per room
- Very rarely seg faults (may be due to empty rooms for testing)



