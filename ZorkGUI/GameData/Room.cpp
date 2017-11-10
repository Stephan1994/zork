#include "Room.h"
#include "Command.h"


Room::Room(string description, int row, int col) {
	this->description = description;
    this->posRow = row;
    this->posCol = col;
    this->enemy = NULL;
}

void Room::setExits(Room *north, int northDoor, Room *east, int eastDoor, Room *south, int southDoor, Room *west, int westDoor) {
	if (north != NULL)
        exits["north"] = make_tuple(north, northDoor);
	if (east != NULL)
        exits["east"] = make_tuple(east, eastDoor);
	if (south != NULL)
        exits["south"] = make_tuple(south, southDoor);
	if (west != NULL)
        exits["west"] = make_tuple(west, westDoor);
}

string Room::shortDescription() {
	return description;
}

string Room::longDescription() {
	return "room = " + description + ".\n" + displayItem() + exitString();
}

string Room::exitString() {
	string returnString = "\nexits =";
    for (map<string, tuple<Room*, int>>::iterator i = exits.begin(); i != exits.end(); i++)
		// Loop through map
		returnString += "  " + i->first;	// access the "first" element of the pair (direction as a string)
	return returnString;
}

Room* Room::nextRoom(string direction) {
    map<string, tuple<Room*, int>>::iterator next = exits.find(direction); //returns an iterator for the "pair"
    if (next == exits.end())
		return NULL; // if exits.end() was returned, there's no room in that direction.
    return get<0>(next->second); // If there is a room, remove the "second" (Room*)
				// part of the "pair" (<string, Room*>) and return it.
}

void Room::addItem(Item *inItem) {
    itemsInRoom.push_back(inItem);
}

//removes item at given index
void Room::removeItem(int index)
{
    int counter = 0;
    for(vector<Item*>::iterator it = itemsInRoom.begin(); it != itemsInRoom.end(); it++, counter++)
    {
        if (counter == index)
        {
            itemsInRoom.erase(it);
            break;
        }
    }
}

//removes first item with given name
void Room::removeItem(string name)
{
    for(vector<Item*>::iterator it = itemsInRoom.begin(); it != itemsInRoom.end(); it++)
    {
        if ((*it)->getName() == name)
        {
            itemsInRoom.erase(it);
            break;
        }
    }
}

int Room::getNumberofItems() const
{
    return itemsInRoom.size();
}

Item* Room::getItemByIndex(int index) const
{
    if (index >= 0 && index < (int)itemsInRoom.size())
        return itemsInRoom.at(index);
    else
        return NULL;
}

/*
void Room::addEnemy(Enemy *inEnemy){
    enemies.push_back(*inEnemy);
}*/

bool Room::enemyAvailable() const
{
    return (enemy != NULL);
}
void Room::setEnemy(Enemy *inEnemy)
{
    this->enemy = inEnemy;
}

void Room::enemyDefeated()
{
    delete enemy;
    this->enemy = NULL;
}

Enemy* Room::getEnemy() const
{
    return enemy;
}

void Room::setRoomPosition(int row, int col)
{
    this->posRow = row;
    this->posCol = col;
}

int Room::getRoomRow() const
{
    return posRow;
}
int Room::getRoomCol() const
{
    return posCol;
}

string Room::displayItem() {
    string tempString = "items in room = ";
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        tempString = "no items in room";
        }
    else if (itemsInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            tempString = tempString + itemsInRoom[x]->getName() + "  " ;
            x++;
            }
        }
    return tempString;
    }

int Room::isItemInRoom(string inString)
{
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        return false;
        }
    else if (itemsInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            // compare inString with short description
            int tempFlag = inString.compare( itemsInRoom[x]->getName());
            if (tempFlag == 0) {
                itemsInRoom.erase(itemsInRoom.begin()+x);
                return x;
            }
            x++;
            }
        }
    return -1;
}

