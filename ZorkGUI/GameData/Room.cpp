#include "Room.h"
#include "Command.h"


Room::Room(string description, int row, int col) {
	this->description = description;
    this->posRow = row;
    this->posCol = col;
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
    //cout <<endl;
    //cout << "Just added" + inItem->getLongDescription();
    itemsInRoom.push_back(*inItem);
}

void Room::addEnemy(Enemy *inEnemy){
    enemies.push_back(*inEnemy);
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
            tempString = tempString + itemsInRoom[x].getShortDescription() + "  " ;
            x++;
            }
        }
    return tempString;
    }

int Room::numberOfItems() {
    return itemsInRoom.size();
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
            int tempFlag = inString.compare( itemsInRoom[x].getShortDescription());
            if (tempFlag == 0) {
                itemsInRoom.erase(itemsInRoom.begin()+x);
                return x;
            }
            x++;
            }
        }
    return -1;
}

