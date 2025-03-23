#ifndef FARKLEGAME_H
#define FARKLEGAME_H

#include "Player.h"
#include <vector>

class FarkleGame
{
private:
    std::vector<Player> players;  // Store the players
    int numPlayers;                // Number of players

    void rollDice(std::vector<int>& dice); // Method to roll dice
    void displayDice(const std::vector<int>& dice); // Method to show dice rolled
    std::vector<int> getScoringDice(const std::vector<int>& dice); // Method to get scoring dice from rolled dice
    int calculateScore(const std::vector<int>& scoringDice); // Caclulates score based on held dice
    void displayLeaderboard(); // Displays scores for all players
    void determineWinner(); // Declare the winner determination function

public:
    FarkleGame(int numPlayers); // Method for starting game logic by naming players.
    void startGame(); // Main method for game logic
};

#endif
