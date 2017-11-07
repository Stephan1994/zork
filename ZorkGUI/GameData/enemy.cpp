#include "enemy.h"

Enemy::Enemy(string name, string picture)
{
    this->name = name;
    this->picture = picture;
}

string Enemy::getName()
{
    return name;
}

string Enemy::getPicture()
{
    return picture;
}
