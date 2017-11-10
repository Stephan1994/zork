#include "item.h"

Item::Item(string name, string path, int damage,  bool quest, bool usable) {
    this->name = name;
    this->picturePath = path;
    this->questItem = quest;
    this->usable = usable;
    this->randPositionX = rand() % 10;
    this->randPositionY = rand() % 10;
    this->damage = damage;

    this->appearenceText = getStory();
}

string Item::getStory()
{
    string out = "Hey, what's that? There is something laying around on the ground. Rather careless if you ask me, I could have snapped my neck!";
    if (questItem)
        out += "It's one of these epic golden coins!! Pick it up quickly before someone else comes.";
    else
        out += "Looks like it is a " + name + ". Pick it up, it could come in handy.";

    return out;
}

string Item::getPicturePath() const
{
    return picturePath;
}

string Item::getName() const
{
    return name;
}

string Item::getLongDescription() const
{
    return "<b>item(s)</b>, <font color='red'>" + name + "</font>.\n";
}

string Item::getAppearenceText() const
{
    return appearenceText;
}

int Item::getDamage() const
{
    return damage;
}

int Item::getXPosition() const
{
    return randPositionX;
}

int Item::getYPosition() const
{
    return randPositionY;
}

bool Item::isQuestItem() const
{
    return questItem;
}

bool Item::isUsable() const
{
    return usable;
}
