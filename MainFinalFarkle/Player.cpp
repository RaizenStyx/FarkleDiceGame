#include "Player.h"
#include <iostream>

using namespace std;

// Default constructor
Player::Player()
{
    name = "";
    score = 0;
    hasEnteredGame = false;

}

// Parameterized constructor
Player::Player(string name)
{
    this->name = name;
    score = 0;
    hasEnteredGame = false;
}

// Getter to get players name
string Player::getName() const
{
    return name;
}

// Getter for getting total score
int Player::getScore() const
{
    return score;
}

// Method to add to total score
void Player::addScore(int points)
{
    score += points;
}

// Method for returning hasEnteredGame 
bool Player::hasEntered() const
{
    return hasEnteredGame;
}

// Method to change the status of hasEnteredGame
void Player::setEntered()
{
    hasEnteredGame = true;
}
