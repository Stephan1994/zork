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
    vector<Room*> rooms;
	Room *currentRoom;
	void createRooms();
	void printWelcome();
	bool processCommand(Command command);
	void printHelp();

    void createItems();
    void displayItems();


public:
    string guiOutput;
	ZorkUL();
	void play();
	string go(string direction);
    void teleport(Command com);
    void goRoom(Command command);
   /* signals:
        void outputChanged(QString);*/
};

#endif /*ZORKUL_H_*/
