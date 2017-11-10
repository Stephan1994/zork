#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "item.h"
#include "enemy.h"
using namespace std;

class Room {

private:
	string description;
	string exitString();
    vector<Item*> itemsInRoom;
    Enemy *enemy;
    int posRow, posCol;
    map<string, std::tuple<Room*, int>> exits;

public:
    Room(string description, int row, int col);

    string shortDescription();
    string longDescription();

    void setExits(Room *north, int northDoor, Room *east, int eastDoor, Room *south, int southDoor, Room *west, int westDoor);
    int getNumberofExits() const;
    bool hasExit(string direction) const;
    Room* getNextRoom(string direction) const;
    int getDoorPosition(string direction) const;

    void addItem(Item *inItem);
    void removeItem(int index);
    void removeItem(string name);
    int getNumberofItems() const;
    Item* getItemByIndex(int index) const;

    void setEnemy(Enemy *inEnemy);
    Enemy* getEnemy() const;
    void enemyDefeated();
    bool enemyAvailable() const;

    void setRoomPosition(int x, int y);
    int getRoomRow() const;
    int getRoomCol() const;

    Room* nextRoom(string direction);

    //depricated
    string displayItem();
    int isItemInRoom(string inString);
};

#endif
