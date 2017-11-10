#include "item.h"

Item::Item(string name, string path, int damage,  bool quest, bool usable) {
    this->name = name;
    this->picturePath = path;
    this->questItem = quest;
    this->usable = usable;
    this->randPositionX = rand() % 10;
    this->randPositionY = rand() % 10;
    this->damage = damage;
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
    return " item(s), " + name + ".\n";
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
