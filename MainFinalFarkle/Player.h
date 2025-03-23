// Player class file
#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
private:
    std::string name; // Player name
    int score; // Player Score
    bool hasEnteredGame; // Used for check to enter player into game with 1000 points

public:
    Player(); // Default constructor
    Player(std::string playerName); // Parameterized constructor
    void addScore(int points); // Method to add to total score
    int getScore() const; // Getter for getting total score
    std::string getName() const; // Getter to get players name
    bool hasEntered() const; // Method for returning hasEnteredGame 
    void setEntered(); // Method to change the status of hasEnteredGame
};

#endif