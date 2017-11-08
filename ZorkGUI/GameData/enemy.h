#ifndef ENEMY_H
#define ENEMY_H

#include <string>
using std::string;

class Enemy
{
public:
    Enemy(string name, string picture, string immunity = "", string weakness = "");
    string getName();
    string getPicture();
    string getImmunity();
    string getWeakness();
    string getDescription();
    int getTimeLimit();
    int health;
    bool time;
private:
    string name;
    string picture;
    int timeLimit;
    int damage;
    string immunity;
    string weakness;
};

#endif // ENEMY_H
