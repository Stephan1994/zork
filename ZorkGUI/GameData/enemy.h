#ifndef ENEMY_H
#define ENEMY_H

#include <string>
using std::string;

class Enemy
{
public:
    Enemy();
    string getName();
    string getPicture();
private:
    string name;
    string picture;
};

#endif // ENEMY_H
