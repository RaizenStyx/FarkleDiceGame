#include "FarkleGame.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>

using namespace std;

FarkleGame::FarkleGame(int numPlayers) 
{
    // Get number of players and resize vector holding them to assign it a length
    this->numPlayers = numPlayers;
    players.resize(numPlayers);

    // Players enter name here
    for (int i = 0; i < numPlayers; i++) 
    {
        cout << "Enter name for Player " << i + 1 << ": ";
        string name;
        cin >> name;
        players[i] = Player(name);
    }
    // Seed random number generator
    srand(static_cast<unsigned int>(time(0))); 
}

void FarkleGame::startGame() 
{
    cout << "Starting Farkle Game!" << endl;

    int currentPlayerIndex = 0; // Keeps track which players turn it is
    bool finalRound = false; // Bool to help with final round, ensures players get one more chance
    int lastRoundStarter = -1; // Used to determine who started last round

    while (true) 
    {
        // Updates player each turn
        Player& currentPlayer = players[currentPlayerIndex];
        cout << "\nIt's " << currentPlayer.getName() << "'s turn!" << endl;

        // Variables needed for logic
        vector<int> dice(6); // Rolled dice
        vector<int> heldDice; // Dice held by player
        int turnPoints = 0; // Points this turn
        bool farkled = false; // Determines if player farkled, thus losing turn

        while (!farkled) 
        {    
            // Dice vector gets resized by subtracting size of held dice
            dice.resize(6 - heldDice.size());

            // If all dice are collected for points, reset and keep going
            if (dice.empty())
            {
                cout << "Hot Dice! Must roll all six dice again." << endl;
                dice.resize(6);
                heldDice.resize(0); 
            }

            // Roll and display dice that were rolled
            rollDice(dice);
            displayDice(dice);

            // Gets the point dice from rolled dice
            vector<int> scoringDice = getScoringDice(dice);

            // If no point dice, then farkle and lose turn
            if (scoringDice.empty()) 
            {
                cout << "Farkle! No scoring dice. Turn over." << endl;
                farkled = true;
                turnPoints = 0;
                break;
            }

            // Shows point dice from rolled dice
            cout << "Scoring dice: ";
            for (int die : scoringDice) cout << die << " ";
            cout << endl;

            // Shows held dice values and points total, if dice are being held
            if (!heldDice.empty()) 
            {
                cout << "Currently held dice: ";
                for (int die : heldDice) cout << die << " ";
                cout << endl;
                turnPoints = calculateScore(heldDice);
                cout << "Currnent points from held dice: " << turnPoints << endl;
            }

            // Variable for player to choose dice
            vector<int> chosenDice; // Vector to hold chosen dice
            char choice;

            cout << "Would you like to set aside any scoring dice? (y/n): ";
            cin >> choice;

            // If player wants to set aside scoring dice
            if (choice == 'y') 
            {
                // Ask Player which dice values they want to keep with spaces between
                cout << "Enter the dice values you want to set aside (space-separated): ";
                int die;
                while (cin >> die) 
                {
                    // Checks if selected dice are in scoring dice
                    auto it = find(scoringDice.begin(), scoringDice.end(), die);
                    if (it != scoringDice.end()) 
                    {
                        chosenDice.push_back(die);
                        scoringDice.erase(it); // Remove one occurrence to prevent over-selection
                    }
                    else 
                    {
                        cout << "Invalid selection or already chosen. Enter valid dice." << endl;
                    }
                    if (cin.peek() == '\n') break;
                }
                // Handle invalid input
                if (cin.fail()) 
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Try again." << endl;
                    continue;
                }

                // Update points and held dice vector 
                heldDice.insert(heldDice.end(), chosenDice.begin(), chosenDice.end());
                turnPoints = calculateScore(heldDice);

            }
            else 
            {
                // If player does not want to set aside dice, check if they can enter game
                if (!currentPlayer.hasEntered() && turnPoints >= 1000) 
                {
                    currentPlayer.setEntered();
                    cout << currentPlayer.getName() << " has officially entered the game!" << endl;
                }
                break;
            }
        }

        // If player has entered game, update score and display leaderboard
        if (turnPoints > 0) 
        {
            if (currentPlayer.hasEntered()) {
                currentPlayer.addScore(turnPoints);
                cout << "Turn ended with " << turnPoints << " points." << endl;
                displayLeaderboard();
            }
        }

        // Check if player has reached 10,000 points to trigger final round 
        if (currentPlayer.getScore() >= 10000 && !finalRound) 
        {
            cout << "\n" << currentPlayer.getName() << " has reached 10,000 points! Final round for other players." << endl;
            finalRound = true;
            lastRoundStarter = currentPlayerIndex;
        }

        // Move to next player
        currentPlayerIndex = (currentPlayerIndex + 1) % numPlayers;
        if (finalRound && currentPlayerIndex == lastRoundStarter) break;
    }
    determineWinner(); // Determine the winner
}

// Rolls dice by generating random values between 1 and 6
void FarkleGame::rollDice(vector<int>& dice) 
{
    for (int& die : dice) {
        die = rand() % 6 + 1;
    }
}

// Displays rolled dice
void FarkleGame::displayDice(const vector<int>& dice) 
{
    cout << "\nYou rolled: ";
    for (int die : dice) 
    {
        cout << die << " ";
    }
    cout << endl;
}

// Gets all scoring (point) dice from rolled dice
vector<int> FarkleGame::getScoringDice(const vector<int>& dice) 
{
    vector<int> scoringDice;
    int counts[7] = { 0 };

    for (int die : dice) 
    {
        counts[die]++;
    }

    for (int i = 1; i <= 6; i++) 
    {
        if (counts[i] >= 3) 
        {
            scoringDice.insert(scoringDice.end(), 3, i);
            counts[i] -= 3;
        }
    }

    for (int i = 1; i <= 6; i++) 
    {
        while (counts[i] > 0) 
        {
            if (i == 1 || i == 5) 
            {
                scoringDice.push_back(i);
            }
            counts[i]--;
        }
    }

    return scoringDice;
}

// Calculates score based on Farkle rules 
int FarkleGame::calculateScore(const vector<int>& scoringDice) 
{
    int score = 0;
    int counts[7] = { 0 };

    for (int die : scoringDice) 
    {
        counts[die]++;
    }

    for (int i = 1; i <= 6; i++) 
    {
        if (counts[i] >= 3) 
        {
            score += (i == 1) ? 1000 : (i * 100);
            counts[i] -= 3;
        }
    }

    score += counts[1] * 100;
    score += counts[5] * 50;

    return score;
}

// Displays all players scores
void FarkleGame::displayLeaderboard() 
{
    cout << "\nLeaderboard:" << endl;
    for (const Player& player : players) 
    {
        cout << player.getName() << ": " << player.getScore() << " points" << endl;
    }
    cout << endl;
}

// Determines winner of game
void FarkleGame::determineWinner() 
{
    Player* winner = &players[0];

    for (Player& player : players) 
    {
        if (player.getScore() > winner->getScore()) 
        {
            winner = &player;
        }
    }

    cout << "\nThe winner is: " << winner->getName() << " with " << winner->getScore() << " points!" << endl;
}