#ifndef ITEM_H_
#define ITEM_H_

#include <string>
using namespace std;

class Item {
private:
	string description;
	string longDescription;
    string picturePath;

public:
    int randPositionX,randPositionY;
    Item (string description, string path);
	string getShortDescription();
    string getLongDescription();
    string getPicturePath();
};

#endif /*ITEM_H_*/
