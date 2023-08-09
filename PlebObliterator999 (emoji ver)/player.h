#ifndef GAME_H
#define GAME_H

#include <unistd.h>
#include <iostream>
#include <sstream>

using namespace std;

void ClearScreen();

//player class
class Player {
    public:
    Player(int x, int y);
    int getScore() const;
    int getWeapon() const;
    void takeDamage(int val);
    void takeTurn();
    string barHealth() const;
    string barHunger() const;
    string barThrist() const;
    string barWeapon() const;
    bool foundWeapon(int newType);
    bool isAlive() const;
    void increaseThrist(int val);
    void increaseHunger(int val);
    void heal(int helth);
    void ArriveAtHideout();
    bool HasReachedHideout() const;

    int x, y;
    private:
    int health, hunger, thirst, score, weapon;
    const int MAX_HEALTH = 8;
    const int MAX_HUNGER = 5;
    const int MAX_THIRST = 5;
    
    //EndTheGame bool for when you reach the BloodRed Rebellion Hideout
    bool EndTheGame = false;
};

//FIGHTENEMY
void fightEnemy(Player& p, string enemy);

#endif