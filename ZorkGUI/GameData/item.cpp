#include "item.h"

Item::Item(string inDescription, string path, int damage,  bool quest, bool usable) {
    this->description = inDescription;
    this->picturePath = path;
    this->questItem = quest;
    this->isUsable = usable;
    this->randPositionX = rand() % 10;
    this->randPositionY = rand() % 10;
    this->damage = damage;
}

string Item::getPicturePath()
{
    return picturePath;
}

string Item::getShortDescription()
{
	return description;
}

string Item::getLongDescription()
{
	return " item(s), " + description + ".\n";
}

int Item::getDamage()
{
    return damage;
}

