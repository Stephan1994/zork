#ifndef ENEMY_H
#define ENEMY_H

#include <string>
using std::string;

class Enemy
{
public:
    Enemy(string name, string picture, string immunity = "", string weakness = "");
    string getName() const;
    string getPicture() const;
    string getImmunity() const;
    string getWeakness() const;
    string getDescription() const;
    string getAppearenceText() const;
    int getTimeLimit() const;
    int getHealth() const;
    void setHealth(int newHealth);
    bool hasTimeLimit() const;

private:
    string name;
    string picture;
    int timeLimit;
    int damage;
    string immunity;
    string weakness;
    int health;
    bool time;
    string appearenceText;
    string createStoryText();
};

#endif // ENEMY_H
