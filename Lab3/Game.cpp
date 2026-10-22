#include "Game.h"
#include <iostream>
#include <random>
#include <algorithm> // for std::advance

using namespace std;

Game::Game() {
    // empty
}

void Game::generatePlayers(int n) {
    for (int i = 0; i < n; i++) {
        players.push_back(new RPG());

        // rename players
        string new_name = "NPC_" + to_string(i);
        players[i]->setName(new_name);
        live_players.insert(i);
    }
}

int Game::selectPlayer() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, live_players.size() - 1);

    // Pick random index
    int randomIndex = dist(gen);

    // Advance iterator to that index
    set<int>::iterator it = live_players.begin();
    advance(it, randomIndex);

    int selectedIndex = *it;
    return selectedIndex;
}

void Game::endRound(RPG *winner, RPG *loser, int loserIndex) {
    // Resets winner's hits_taken to 0.
    winner->setHitsTaken(0);

    // Removes the loser from the live_players.
    live_players.erase(loserIndex);

    // Calls updateExpLevel() for the winner
    winner->updateExpLevel();

    // prints the structure "NPC_X won against NPC_Y"
    cout << winner->getName() << " won against " << loser->getName() << endl;
}

void Game::battleRound() {
    int playInd1 = selectPlayer();
    int playInd2 = selectPlayer();

    if (playInd1 == playInd2) {
        battleRound();
        return;
    }

    RPG* player1 = players[playInd1];
    RPG* player2 = players[playInd2];

    while (player1->isAlive() && player2->isAlive()) {
        player1->attack(player2);
        if (player2->isAlive()) {
            player2->attack(player1);
        }
    }

    if (player1->isAlive()) {
        endRound(player1, player2, playInd2);
    } else { // player2 won
        endRound(player2, player1, playInd1);
    }
}

void Game::gameLoop() {
    while (live_players.size() > 1) {
        battleRound();
    }
}

void Game::printFinalResults() {
    for (int i = 0; i < players.size(); i++) {
        players[i]->printStats();
    }
}

Game::~Game() {
    // Destroy the Game object - delete all dynamically allocated RPG objects
    for (RPG* p : players) {
        delete p;
    }
    players.clear();
}