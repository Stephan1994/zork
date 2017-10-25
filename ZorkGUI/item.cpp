#include "item.h"

Item::Item(string inDescription, string path) {
    this->description = inDescription;
    this->picturePath = path;
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

