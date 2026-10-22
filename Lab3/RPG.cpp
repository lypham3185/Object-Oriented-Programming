// RPG.cpp
// Ly
#include "RPG.h"
#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

RPG::RPG() {
    name = "NPC";
    hits_taken = 0;
    luck = 0.1;
    exp = 50.0;
    level = 1;
}

RPG::RPG(string name, int hits_taken, float luck, float exp, int level) {
    this->name = name;
    this->hits_taken = hits_taken;
    this->luck = luck;
    this->exp = exp;
    this->level = level;
}

RPG::~RPG() {
}

/**
 * @brief sets hits_taken to new_hits
 */
void RPG::setHitsTaken(int new_hits) {
    hits_taken = new_hits;
}

/**
 * @brief returns whether hits_taken is less than MAX_HITS_TAKEN
 * In other words, a player is alive as long as they have not been hit MAX_HITS_TAKEN times.
 *
 * @return true : player is alive
 * @return false : player is unalive
 */
bool RPG::isAlive() const {
    return hits_taken < MAX_HITS_TAKEN;
}

string RPG::getName() const {
    return name;
}

int RPG::getHitsTaken() const {
    return hits_taken;
}

float RPG::getLuck() const {
    return luck;
}

float RPG::getExp() const {
    return exp;
}

int RPG::getLevel() const {
    return level;
}

void RPG::setName(string name) {
    this->name = name;
}

void RPG::updateExpLevel() {
    exp += 50.0f;
    if (exp >= 100.0f) {
        level += 1;
        exp = 0.0f;
        luck += 0.1f;
    }
}

void RPG::attack(RPG * opponent) {
    random_device rd;
    mt19937 gen(rd()); // seed with random
    uniform_real_distribution<double> dis(0.0, 1.0);

    float random_num = dis(gen);

    // Create a bool called hit
    // hit is true if random_num > HIT_FACTOR * opponent's luck
    bool hit = random_num > HIT_FACTOR * opponent->getLuck();

    // if hit is true, call setHitsTaken() to increase opponent's hits_taken
    if (hit) {
        opponent->setHitsTaken(opponent->getHitsTaken() + 1);
    }
}

void RPG::printStats() {
    cout << "Name: " << name 
         << "\tHits Taken: " << hits_taken 
         << "\tLuck: " << fixed << setprecision(6) << luck 
         << " Exp: " << exp 
         << " Level: " << level 
         << "\tStatus: " << (isAlive() ? "Alive" : "Dead") << endl;
}