#ifndef GAME_LANDFORMS_H
#define GAME_LANDFORMS_H

#include <iostream>
#include <unistd.h>
#include "player.h"

using namespace std;

//landforms
class Land {
    public:
    virtual string getDescription() = 0;
    virtual string visit(Player& player) = 0;
    void printTexture(int row);
    
    protected:
    string texture[4];
};

class Forest : public Land {
    public:
    Forest();
    string getDescription();
    string visit(Player& player);
};

class Lake : public Land {
    public:
    Lake();
    string getDescription();
    string visit(Player& player);
};

class Plain : public Land {
    public:
    Plain();
    string getDescription();
    string visit(Player& player);
};

class Town : public Land {
    public:
    Town();
    string getDescription();
    string visit(Player& player);
};

class Desert : public Land {
    public:
    Desert();
    string getDescription();
    string visit(Player& player);
};

class WeaponStorageFacility : public Land {
    public:
    WeaponStorageFacility();
    string getDescription();
    string visit(Player& player);
};

class SecretRebellionHideout : public Land {
    public:
    SecretRebellionHideout();
    string getDescription();
    string visit(Player& player);
};

#endif