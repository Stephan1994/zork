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

    this->appearenceText = createStoryText();
}

string Enemy::createStoryText()
{
    string out = "A wild " + name + " appeared. It seems like it wants to fight. Try to defeat it!\n";
    if (immunity != "")
        out += "You should be carefull with a " + immunity + ". I think it isn't quite effective against this enemy.";
    if (weakness != "")
        out += "There are many possibilities in defeating this enemy. But the best one would be using a " + weakness + ". It's very effective!";
    if(time)
        out += "Hurry up! It will attack you in " + to_string(timeLimit) + "! You have to beat it before.\n";
    out += "Enemy: " + name + "\n";
    out += "Health: " + to_string(health) + "\n";
    out += "Damage: " + to_string(damage) + "\n";

    return out;
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

string Enemy::getAppearenceText() const
{
    return appearenceText;
}
