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
    Room *currentRoom;
    Player *player;
    Room *rooms[10][10];
    int maxRoomsRow;
    int maxRoomsCol;

	void createRooms();
    void startStory();

public:
    string guiOutput;
    ZorkUL(int roomsRow, int roomsCol);
    ~ZorkUL();
	void play();
	string go(string direction);
    void teleport(Command com);
    void goRoom(Command command);

    inline Room* getCurrentRoom() const
    {
        return currentRoom;
    }
    inline Player* getPlayer() const
    {
        return player;
    }
    Room* getRoom(int row, int col) const;
    int getMaxRoomsRow() const;
    int getMaxRoomsCol() const;
};

#endif /*ZORKUL_H_*/
