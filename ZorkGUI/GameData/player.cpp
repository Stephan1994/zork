#include "player.h"

Player::Player(string description)
{
    this->description = description;
}

void Player::addItem(Item item)
{
    carriedItems.push_back(item);
}

void Player::addQuestItem(Item item)
{
    carriedQuestItems.push_back(item);
}
