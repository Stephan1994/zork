#include "player.h"

Player::Player(string description)
{
    this->description = description;
}

void Player::addItem(Item item) {
    carriedItems.push_back(item);
}
