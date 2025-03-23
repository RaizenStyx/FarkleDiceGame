// Name: Connor Reed
// Course: IT-312
// Date: 2/23/2025
// Project Number: 7-1 Final Project Farkle Dice Game
//
// Program description: This program requires at least 2 players to be played with no upper limit.
// On start up, it will show the rules and wait for input before starting. 
// Next, it will asks for number of players and their names.
// Player 1 goes first, then 2 ect. Player will roll 6 dice and decide to keep ones that are scoring.
// Once player decides not to roll again, if they gain more than 1k points, they will enter the game. 
// If no point dice are rolled, the players turn ends. 
// Goal is to enter game first by getting 1k points, then work up to 10k to start a final round. 
// 
// MainFarkleGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include "Player.h"
#include "FarkleGame.h"


using namespace std;

// Method to display rules by reading in the Rules.txt file
void displayRules(const string& filename)
{
    ifstream rulesFile(filename);

    if (!rulesFile)
    {
        cout << "Error: Could not open rules file.\n";
        return;
    }

    string line;
    while (getline(rulesFile, line))
    {
        cout << line << endl;
    }

    rulesFile.close();
    cout << "\nPress Enter to continue playing...";
    cin.ignore(); // Wait for user input before proceeding
}


int main()
{
    displayRules("Rules.txt");

    int numPlayers;
    do // do while loop to ensure at least 2 players are playing
    {
        cout << "Enter number of players (minimum 2): ";
        cin >> numPlayers;
    } while (numPlayers < 2);

    // Start game with FarkleGame class
    FarkleGame game(numPlayers);
    game.startGame();

    return 0;
}

