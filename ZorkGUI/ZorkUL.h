#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "item.h"
#include <iostream>
#include <string>
#include <QString>
using namespace std;

class ZorkUL {
private:
	Parser parser;
	void createRooms();
	void printWelcome();
	bool processCommand(Command command);
	void printHelp();
    void createItems();
    void displayItems();


public:
    string guiOutput;
    Room *currentRoom;
    Room *rooms[50][50];
    int maxRoomsRow;
    int maxRoomsCol;
    ZorkUL(int roomsRow, int roomsCol);
	void play();
	string go(string direction);
    void teleport(Command com);
    void goRoom(Command command);
   /* signals:
        void outputChanged(QString);*/
};

#endif /*ZORKUL_H_*/
