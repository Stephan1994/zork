#include "item.h"

Item::Item(string inDescription, string path, bool quest) {
    this->description = inDescription;
    this->picturePath = path;
    this->questItem = quest;
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

