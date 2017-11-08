#ifndef ITEM_H_
#define ITEM_H_

#include <string>
using namespace std;

class Item {
private:
	string description;
	string longDescription;
    string picturePath;
    int damage;

public:
    int randPositionX,randPositionY;
    Item (string description, string path, int damage, bool quest = false, bool usable = true);
	string getShortDescription();
    string getLongDescription();
    string getPicturePath();
    int getDamage();
    bool questItem;
    bool isUsable;
};

#endif /*ITEM_H_*/
