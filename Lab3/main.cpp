// main.cpp
// Ly
#include <iostream>
#include "RPG.h"
#include "Game.h"

using namespace std;

int main()
{
    // Create a Game object
    Game my_game = Game();

    // Create num_players as an int and set it to 10
    int num_players = 10;

    // Call generatePlayers(...) with num_players as the parameter
    my_game.generatePlayers(num_players);

    // Call gameLoop()
    my_game.gameLoop();

    // Call printFinalResults()
    my_game.printFinalResults();

    return 0;
}