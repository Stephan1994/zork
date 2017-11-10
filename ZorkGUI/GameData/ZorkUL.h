#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "Command.h"
#include "Room.h"
#include "item.h"
#include "player.h"

#include <iostream>
#include <string>
#include <QString>
using namespace std;

class ZorkUL {
private:
	void createRooms();
	void printWelcome();
	bool processCommand(Command command);
	void printHelp();
    void createItems();
    void displayItems();

public:
    string guiOutput;
    Room *currentRoom;
    Player *player;
    //Character *charac;
    Room *rooms[50][50];
    int maxRoomsRow;
    int maxRoomsCol;
    ZorkUL(int roomsRow, int roomsCol);
    ~ZorkUL();
	void play();
	string go(string direction);
    void teleport(Command com);
    void goRoom(Command command);
};

#endif /*ZORKUL_H_*/
