#include "player.h"

Player::Player(string description)
{
    this->description = description;
}

void Player::addItem(Item *item)
{
    carriedItems.push_back(item);
}

//returns number of carried items without quest items
int Player::numberOfCarriedItems() const
{
    int counter = 0;
    for(vector<Item*>::const_iterator it = carriedItems.begin(); it != carriedItems.end(); it++)
    {
        if(!(*it)->isQuestItem())
            counter++;
    }
    return counter;
}

//returns number of carried quest items
int Player::numberOfCarriedQuestItems() const
{
    int counter = 0;
    for(vector<Item*>::const_iterator it = carriedItems.begin(); it != carriedItems.end(); it++)
    {
        if((*it)->isQuestItem())
            counter++;
    }
    return counter;
}

//returns item at given position and ignores quest items
Item* Player::getItemByIndex(int index) const
{
    int counter = 0;
    for(vector<Item*>::const_iterator it = carriedItems.begin(); it != carriedItems.end(); it++)
    {
        if (!(*it)->isQuestItem())
        {
            if(counter == index)
                return *it;

            counter++;
        }
    }

    return NULL;
}

//removes item at given index ignoring quest items
void Player::removeItem(int index)
{
    int counter = 0;
    for(vector<Item*>::iterator it = carriedItems.begin(); it != carriedItems.end(); it++)
    {
        if(!(*it)->isQuestItem())
        {
            if (counter == index)
            {
                delete *it;
                carriedItems.erase(it);
                break;
            }
            counter++;
        }
    }
}

//removes first item with given name
void Player::removeItem(string name)
{
    for(vector<Item*>::iterator it = carriedItems.begin(); it != carriedItems.end(); it++)
    {
        if ((*it)->getName() == name)
        {
            delete *it;
            carriedItems.erase(it);
            break;
        }
    }
}

/*void Player::addQuestItem(Item *item)
{
    carriedQuestItems.push_back(item);
}

void Player::numberOfCarriedQuestItems() const
{
    return carriedQuestItems.size();
}*/
