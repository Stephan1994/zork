#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "item.h"
#include "enemy.h"
using namespace std;
using std::vector;

class Room {

private:
	string description;
	string exitString();

public:
    int numberOfItems();
    int posRow, posCol;
    map<string, std::tuple<Room*, int>> exits;
    vector<Item> itemsInRoom;
    vector<Enemy> enemies;

    Room(string description, int row, int col);
    void setExits(Room *north, int northDoor, Room *east, int eastDoor, Room *south, int southDoor, Room *west, int westDoor);
	string shortDescription();
	string longDescription();
	Room* nextRoom(string direction);
    void addItem(Item *inItem);
    void addEnemy(Enemy *inEnemy);
    string displayItem();
    int isItemInRoom(string inString);
    void removeItemFromRoom(int location);
};

#endif
