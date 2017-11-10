#include "enemy.h"
using std::to_string;

Enemy::Enemy(string name, string picture, string immunity, string weakness)
{
    this->name = name;
    this->picture = picture;
    this->health = rand() % 81 + 20; //number between 20 and 100
    this->time = (rand() % 2 == 0) ? true : false;
    if (time)
        this->timeLimit = rand() % 9 + 2; //number between 2 and 10
    this->damage = rand() % 21 + 5; //number between 5 and 20

    this->immunity = immunity;
    this->weakness = weakness;
}

string Enemy::getName() const
{
    return name;
}

string Enemy::getDescription() const
{
    string out = name + "\nHealth: " + to_string(health) + "\nDamage: " + to_string(damage);
    if (immunity != "")
        out += "\nImmunity: " + immunity;
    if (weakness != "")
        out += "\nWeakness: " + weakness;
    return out;
}

string Enemy::getPicture() const
{
    return picture;
}

string Enemy::getWeakness() const
{
    return weakness;
}

string Enemy::getImmunity() const
{
    return immunity;
}

int Enemy::getTimeLimit() const
{
    return timeLimit;
}

bool Enemy::hasTimeLimit() const
{
    return time;
}

int Enemy::getHealth() const
{
    return health;
}

void Enemy::setHealth(int newHealth)
{
    if (newHealth <= 100)
            this->health = newHealth;
    else
        this->health = 100;
}
