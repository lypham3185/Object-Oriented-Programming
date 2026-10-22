#ifndef GAME_H
#define GAME_H

#include <vector>
#include <set>
#include "RPG.h"

using namespace std;

class Game {
private:
    vector<RPG*> players;
    set<int> live_players;

public:
    Game();
    void generatePlayers(int n);
    int selectPlayer();
    void endRound(RPG* winner, RPG* loser, int loserIndex);
    void battleRound();
    void gameLoop();
    void printFinalResults();
    ~Game();
};

#endif