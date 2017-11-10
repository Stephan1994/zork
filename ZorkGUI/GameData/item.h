#ifndef ITEM_H_
#define ITEM_H_

#include <string>
using namespace std;

class Item {
private:
    string name;
	string longDescription;
    string picturePath;
    string appearenceText;
    int damage;
    int randPositionX,randPositionY;
    bool questItem;
    bool usable;

    string getStory();

public:
    Item (string name, string path, int damage, bool quest = false, bool usable = true);
    string getName() const;
    string getLongDescription() const;
    string getPicturePath() const;
    string getAppearenceText() const;
    int getDamage() const;
    int getXPosition() const;
    int getYPosition() const;
    bool isQuestItem() const;
    bool isUsable() const;

};

#endif /*ITEM_H_*/
