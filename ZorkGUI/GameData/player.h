#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using std::string;
#include "item.h"
#include <vector>
using std::vector;

class Player
{
private:
    string description;
    vector <Item*> carriedItems;
public:
    Player(string description);
    void addItem(Item *item);
    void removeItem(int index);
    void removeItem(string name);
    Item* getItemByIndex(int index) const;
    int numberOfCarriedItems() const;
    int numberOfCarriedQuestItems() const;
};

#endif // PLAYER_H
