#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "ZorkUL.h"

#include <string>
using namespace std;
#include <vector>
using std::vector;

class Character {
private:
	string description;
    //vector<Item> carriedItems;
public:
    Character(string description);
    //void addItems(Item &Item);
    //string shortDescription();
    //string longDescription();

};

#endif /*CHARACTER_H_*/
