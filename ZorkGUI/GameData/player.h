#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using std::string;
#include "item.h"
#include <vector>
using std::vector;

class Player
{
public:
    Player(string description);
    string description;
    vector <Item> carriedItems;
    vector <Item> carriedQuestItems;
    void addItem(Item item);
    void addQuestItem(Item item);
};

#endif // PLAYER_H
