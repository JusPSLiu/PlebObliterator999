#include <iostream>
#include <sstream>
#include <time.h>
#include <unistd.h>
#include <cstring>

using namespace std;

bool EndTheGame = false;

void ClearScreen() {
    cout << "\033[2J\033[3J" << endl;
}

class Player {
    public:
    Player(int x, int y){
        health = MAX_HEALTH;
        hunger = MAX_HUNGER;
        thirst = MAX_THIRST;

        this->x = x;
        this->y = y;
        this->score = 0;
        this->weapon = 0;
    }

    int getScore() const {
        return score;
    }

    int getWeapon() const {
        return weapon;
    }

    void takeDamage(int val){
        this->health -= val;
        if(this->health < 0) this->health = 0;
    }

    void takeTurn(){
        this->thirst--;
        this->hunger--;

        if(this->thirst <= 0){
            this->health--;
            this->thirst = 0;
        }

        if(this->hunger <= 0){
            this->health--;
            this->hunger = 0;
        }

        this->score++;
    }

    string barHealth() const {
        stringstream ss;
        ss << "\033[0mHealth: \033[1;41m";
        for (int i = 0; i < this->health; i++) ss << "|";
        return ss.str();
    }


    string barHunger() const {
        stringstream ss;
        ss << "\033[0mHunger: \033[1;43m";
        for (int i = 0; i < this->hunger; i++) ss << "|";
        return ss.str();
    }


    string barThrist() const {
        stringstream ss;
        ss << "\033[0mThrist: \033[1;44m";
        for (int i = 0; i < this->thirst; i++) ss << "|";
        return ss.str();
    }
    
    string barWeapon() const {
        string wep = "\033[0m\tCurrent Weapon: \033[1;100m";
        switch(weapon) {
            case 0: wep += "✊\033[0m"; break;
            case 1: wep += "\033[33m\\\033[0m"; break;
            case 2: wep += "🗡\033[0m️"; break;
        }
        
        return wep;
    }

    bool foundWeapon(int newType) {
        //if have better then say false so that it doesnt say every time you find a weapon
        if (weapon >= newType) return false;

        //set the weapon and return true that it has been upgraded
        weapon = newType;
        return true;
    }

    bool isAlive() const {
        return this->health > 0;
    }

    void increaseThrist(int val){
        this->thirst += val;
        if(this->thirst > MAX_THIRST) this->thirst = MAX_THIRST+1;//+1 because it immediately goes down 1
    }

    void increaseHunger(int val){
        this->hunger += val;
        if(this->hunger > MAX_HUNGER) this->hunger = MAX_HUNGER+1;//+1 because it immediately goes down 1
    }

    void heal(int helth) {
        health += helth;
        if (health > MAX_HEALTH) {
            health = MAX_HEALTH;
        }
    }

    int x, y;
    private:
    int health, hunger, thirst, score, weapon;
    const int MAX_HEALTH = 8;
    const int MAX_HUNGER = 5;
    const int MAX_THIRST = 5;
};

void fightEnemy(Player&, string);

class Land {
    public:
    virtual string getDescription() = 0;
    virtual string visit(Player& player) = 0;
    void printTexture(int row) {
        if (row < 3) {
            //if row is 0 1 or 2 then dont have to insert player in center
            cout << texture[row];
        } else {
            //if row is 3, 4 or 5 that means player there. texture[3] has the player
            if (row == 4) cout << texture[3];
            else cout << texture[row-3];
        }
    }
    
    protected:
    string texture[4];
};

// TODO: Define at least 3 more types of derivded land types
// TODO: Add some unique effect to each new type

class Forest : public Land {
    public:
    Forest() {
        //randomize texture
        for (int i=0;i<3;i++) {
            switch(rand() % 4) {
                case 0:
                    texture[i] = "\033[1;32;42m▒▒🌲🌲";
                    if (i==1) texture[3] = "\033[1;32;42m▒▒😐🌲";
                    break;
                case 1:
                    texture[i] = "\033[1;32;42m🌲▒▒🌲";
                    if (i==1) texture[3] = "\033[1;32;42m🌲😐🌲";
                    break;
                case 2:
                    texture[i] = "\033[1;32;42m🌲🌲▒▒";
                    if (i==1) texture[3] = "\033[1;32;42m🌲😐▒▒";
                    break;
                case 3:
                    texture[i] = "\033[1;32;42m▒▒🌲▒▒";
                    if (i==1) texture[3] = "\033[1;32;42m▒▒😐▒▒";
                    break;
            }
        }
    }
    
    string getDescription(){
        return "a densely wooded forest";
    }

    string visit(Player& player){
        int randomNum = rand() % 100;

        if(randomNum > 74){
            fightEnemy(player, "BEAR");
            return "You were attacked by a bear lol";
        } else if(randomNum > 20){
            player.increaseHunger(2);
            //if the weapon is new then say this
            if (player.foundWeapon(1)) {
                return "You found some berries and a new stick weapon!";
            }
            //otherwise just send normal message
            return "You forage for berries in the woods and eat a few.";
        } else {
            player.increaseHunger(2);
            return "You forage for berries in the woods and eat a few.";
        }
    }
};

class Lake : public Land {
    public:
    Lake() {
        //randomize texture
        for (int i=0;i<3;i++) {
            switch(rand() % 4) {
                case 0:
                    texture[i] = "\033[1;34;44m▓▓▓▒▒▒";
                    if (i==1) texture[3] = "\033[1;34;44m▓▓\033[43m😐\033[44m▒▒";
                    break;
                case 1:
                    texture[i] = "\033[1;34;44m▒▒▒▒▓▓";
                    if (i==1) texture[3] = "\033[1;34;44m▒▒\033[43m😐\033[44m▓▓";
                    break;
                case 2:
                    texture[i] = "\033[1;34;44m▓▓▒▓▒▓";
                    if (i==1) texture[3] = "\033[1;34;44m▓▓\033[43m😐\033[44m▒▓";
                    break;
                case 3:
                    texture[i] = "\033[1;34;44m▒▓▒▒▒▒";
                    if (i==1) texture[3] = "\033[1;34;44m▒▓\033[43m😐\033[44m▒▒";
                    break;
            }
        }
    }
    
    string getDescription(){
        return "a clear sparkling lake";
    }

    string visit(Player& player){
        player.increaseThrist(2);
        
        int randomNum = rand() % 100;
        if (randomNum > 75) {
            fightEnemy(player, "SEA MONSTER");
            return "You were attacked by a sea monster while on your boat";
        }
        return "You take a boat onto the lake and drink its clean water";
    }
};

class Plain : public Land {
    public:
    Plain() {
        if (rand() % 100 < 50) {
            texture[0] = "\033[1;32;42m▓▒▓▒▓▒";
            texture[1] = "\033[1;32;42m▒▓▒▓▒▓";
            texture[2] = "\033[1;32;42m▓▒▓▒▓▒";
            texture[3] = "\033[1;32;42m▒▓😐▒▓";
        } else {
            texture[0] = "\033[1;32;42m▒▓▒▓▒▓";
            texture[1] = "\033[1;32;42m▓▒▓▒▓▒";
            texture[2] = "\033[1;32;42m▒▓▒▓▒▓";
            texture[3] = "\033[1;32;42m▓▒😐▓▒";
        }
    }
    
    string getDescription(){
        return "an open field";
    }

    string visit(Player& player){
        if (rand() % 100 > 85) {
            fightEnemy(player, "COW");
            return "You were attacked by a cow";
        }
        return "You relax and sit there";
    }
};

class Town : public Land {
    public:
    Town() {
        for (int i=0;i<3;i++) {
            switch(rand() % 4) {
                case 0:
                    if (i==1) {
                        texture[3] = "\033[1;32;42m▒▓😐🏠";
                        texture[1] = "\033[1;32;42m▒▓🏠🏠";
                    } else texture[i] = "\033[1;32;42m▓▒🏠🏠";
                    break;
                case 1:
                    if (i==1) {
                        texture[3] = "\033[1;32;42m🏠😐▒▓";
                        texture[1] = "\033[1;32;42m🏠🏠▒▓";
                    } else texture[i] = "\033[1;32;42m🏠🏠▓▒";
                    break;
                case 2:
                    if (i==1) {
                        texture[3] = "\033[1;32;42m▒▓😐▒▓";
                        texture[1] = "\033[1;32;42m▒▓🏠▒▓";
                    } else texture[i] = "\033[1;32;42m▓▒🏠▓▒";
                    break;
                case 3:
                    if (i==1) {
                        texture[3] = "\033[1;32;42m▒▓😐🏠";
                        texture[1] = "\033[1;32;42m▒▓▒▓🏠";
                    } else texture[i] = "\033[1;32;42m▓▒▓▒🏠";
                    break;
                case 4:
                    texture[i] = "\033[1;42m🏠🏠🏠";
                    if (i==1) texture[3] = "\033[1;42m🏠😐🏠";
                    break;
            }
        }
    }
    
    string getDescription(){
        return "a town";
    }

    string visit(Player& player){
        int randomNum = rand() % 100;
        
        if (randomNum > 85) {
            fightEnemy(player, "MORTAL PLEBIAN");
            return "You were attacked by an impoverished rebellious individual";
        } else if (randomNum > 77) {
            fightEnemy(player, "DOG");
            if (randomNum > 80) return "A local attacked you with their dog";
            return "You were attacked by a stray dog";
        } else {
            player.increaseThrist(2);
            player.increaseHunger(2);
            player.heal(1);
            return "You exercise your quartering rights to eat food, drink water and heal";
        }
    }
};

class Desert : public Land {
    public:
    Desert() {
        if (rand() % 100 < 50) {
            texture[0] = "\033[1;33;43m▓▒▓▒▓▒";
            texture[1] = "\033[1;33;43m▒▓▒▓▒▓";
            texture[2] = "\033[1;33;43m▓▒▓▒▓▒";
            texture[3] = "\033[1;33;43m▒▓😐▒▓";
        } else {
            texture[0] = "\033[1;33;43m▒▓▒▓▒▓";
            texture[1] = "\033[1;33;43m▓▒▓▒▓▒";
            texture[2] = "\033[1;33;43m▒▓▒▓▒▓";
            texture[3] = "\033[1;33;43m▓▒😐▓▒";
        }
    }
    
    string getDescription(){
        return "a desert";
    }

    string visit(Player& player){
        if (rand() % 10 > 7) {
            player.increaseThrist(2);
            player.increaseHunger(3);
            return "You found a dead guy's supplies and feel revitalized";
        }
        player.increaseThrist(-1);
        return "You are now really dry and thirsty";
    }
};

class WeaponStorageFacility : public Land {
    public:
    WeaponStorageFacility() {
        texture[0] = "\033[1;32;42m▒▓▒▓▒▓";
        texture[1] = "\033[1;32;42m▓\033[1;37;100m▒🗡️▓\033[1;32;42m▒";
        texture[2] = "\033[1;32;42m▒▓▒▓▒▓";
        texture[3] = "\033[1;32;42m▓\033[1;37;100m▒😐▓\033[1;32;42▒";
    }
    
    string getDescription(){
        return "the secret rebel weapon storage facility";
    }

    string visit(Player& player){
        if (player.foundWeapon(2))
            return "You found a sword in the rebel weapon storage facility and are now prepared to quell the insurgency";
        return "There's nothing more to do here.";
    }
};

class SecretRebellionHideout : public Land {
    public:
    SecretRebellionHideout() {
        texture[0] = "\033[1;31;41m▒▓▒▓▒▓";
        texture[1] = "\033[1;31;41m▓\033[1;37;100m▒▓▒▓\033[1;31;41m▒";
        texture[2] = "\033[1;31;41m▒▓▒▓▒▓";
        texture[3] = "\033[1;31;41m▓\033[1;37;100m▒😐▓\033[1;31;41m▒";
    }
    
    string getDescription( ){
        return "BloodRed Secret Hideout. You should only enter after you obtain a sword.";
    }

    string visit(Player& player){
        EndTheGame = true;
        return "You enter the rebellion hideout";
    }
};

const int MAP_SIZE = 20;
Land* map[MAP_SIZE][MAP_SIZE];

void populateMap(){
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            // TODO: Modify this code to add your new land types
            int randomNum = rand() % 11;
            switch(randomNum){
                case 0 ... 2: // Forest
                    map[i][j] = new Forest;
                    break;
                case 3 ... 5: // Lake
                    map[i][j] = new Lake;
                    break;
                case 6 ... 7: // Plain
                    map[i][j] = new Plain;
                    break;
                case 8: // Town
                    map[i][j] = new Town;
                    break;
                case 9 ... 10: // Desert
                    map[i][j] = new Desert;
                    break;
                default:
                    cout << "Invalid land type selected" << endl;
                    break;
            }
        }
    }
    
    // generate the hidden storage facility and hideout
    int randomNum = rand() % ((MAP_SIZE-1)*4);
    int hideoutLocation[] = {MAP_SIZE/2+((rand() % 5) -2), MAP_SIZE/2+((rand() % 5) -2)};
    
    //failsafe in case MAP_SIZE is smol
    hideoutLocation[0] = abs(hideoutLocation[0]) % MAP_SIZE;
    hideoutLocation[1] = abs(hideoutLocation[1]) % MAP_SIZE;
    
    if (hideoutLocation[0] == (int)MAP_SIZE*0.5 && hideoutLocation[1] == (int)MAP_SIZE*0.5) {
        hideoutLocation[0]--;
    }
    
    switch (randomNum % 4) {
        case 0:
            randomNum *= 0.25;
            //delete map[0][randomNum]; APPARENTLY I WAS DOUBLE DELETING  D:<
            map[0][randomNum] = new WeaponStorageFacility;
            
            //make sure hideout not overlapping
            if (hideoutLocation[0] == 0 && hideoutLocation[1] == randomNum) {
                hideoutLocation[0]++;
                hideoutLocation[1]++;
            }
            break;
        case 1:
            randomNum *= 0.25;
            //delete map[0][randomNum];
            map[MAP_SIZE-1][randomNum] = new WeaponStorageFacility;
            
            //make sure hideout not overlapping
            if (hideoutLocation[0] == MAP_SIZE-1 && hideoutLocation[1] == randomNum) {
                hideoutLocation[0]--;
                hideoutLocation[1]++;
            }
            break;
        case 2:
            randomNum *= 0.25;
            //delete map[0][randomNum];
            map[randomNum][0] = new WeaponStorageFacility;
            
            //make sure hideout not overlapping
            if (hideoutLocation[0] == randomNum && hideoutLocation[1] == 0) {
                hideoutLocation[0]++;
                hideoutLocation[1]++;
            }
            break;
        default:
            randomNum *= 0.25;
            //delete map[0][randomNum];
            map[randomNum][MAP_SIZE-1] = new WeaponStorageFacility;
            
            //make sure hideout not overlapping
            if (hideoutLocation[0] == randomNum && hideoutLocation[1] == MAP_SIZE-1) {
                hideoutLocation[0]++;
                hideoutLocation[1]--;
            }
            break;
    }
    
    //I'M WRITING new SO MUCH BUT I CHECKED THE ADDRESSES. HOW IS THIS NOT LEAKING MEMORY.
    //delete map[hideoutLocation[0]][hideoutLocation[1]];
    map[hideoutLocation[0]][hideoutLocation[1]] = new SecretRebellionHideout;
}

void SlowPrint(string printOut) {
    for (int i=0;i<printOut.length();i++) {
        cout << printOut.at(i) << flush;
        usleep(100000);
    }
    cout << endl;
}

int main(int args, char* argv[]){
    srand(time(0));

    populateMap();

    Player player(MAP_SIZE*1.5, MAP_SIZE*1.5);
    //player coords go from MAP_SIZE to 2×MAP_SIZE so the gui doesnt fail with negative mod
    
    //usage: test -skip -sword
    if (args > 1 && !(strcmp(argv[1],"-skip") != 0 || strcmp(argv[1],"-noskip") != 0)) {
        cout << "     Usage: ./Project7 -skip -sword\n\tOR: ./Project7 -noskip -sword" << endl;
        usleep(2000000);
        cout << "\n\t  \"-skip\" skips the opening cutscene, \"-noskip\" does not" << endl;
        cout << "\t  \"-sword\" gives you the most powerful weapon in the game right from the start" << endl;
        return 1;
    }
    
    //debug cheat code for instant sword
    if (args > 2 && strcmp(argv[2],"-sword") == 0) player.foundWeapon(2);

    if (args <= 1 || strcmp(argv[1],"-skip") != 0) {
        ClearScreen();
        cout << "Some random plebians are trying to overthrow the ruling class." << endl;
        usleep(4000000);
        cout << "It's time to put them in their place." << endl;
        usleep(4000000);
        ClearScreen();
        cout << "Their leader is hiding in the BloodRed Rebellion Hideout." << endl;
        usleep(4000000);
        cout << "Nobody knows where it is, and all weapons have been taken." << endl;
        usleep(4000000);
        ClearScreen();
        cout << "You must go and find the secret rebellion weapon facility" << endl;
        usleep(4000000);
        cout << "and grab a sword to destroy the rebel leader once and for all!" << endl;
        usleep(4000000);
    }
    
    //clear the screen
    ClearScreen();

    while(player.isAlive() && !EndTheGame){
        //print the map
        //top row
        for (int i=0;i<3;i++) {
            for (int j=0;j<5;j++) {
                map[(player.x-2+j) % MAP_SIZE][(player.y - 1) % MAP_SIZE]->printTexture(i);
            }
            //print the stats
            switch(i) {
                case 0:
                    cout << "\033[0m\t" << player.barHealth() << endl;
                    break;
                case 1:
                    cout << "\033[0m\t" << player.barHunger() << endl;
                    break;
                case 2:
                    cout << "\033[0m\t" << player.barThrist() << endl;
                    break;
            }
        }
        //mid row
        for (int i=0;i<3;i++) {
            for (int j=0;j<5;j++)
                if (j==2)
                    // add 3 to tell map a message that its the center
                    map[player.x % MAP_SIZE][(player.y) % MAP_SIZE]->printTexture(i+3);
                else {
                    map[(player.x-2+j) % MAP_SIZE][(player.y) % MAP_SIZE]->printTexture(i);
                }
            //if (i == 0) then print the weapon, if (i == 2) then print the north part on the side
            if (i == 0) {
                cout << player.barWeapon() << endl;
            } else if (i == 1) {
                cout << endl;
            } else cout << "\033[0m\tNorth: " << map[player.x % MAP_SIZE][(player.y - 1) % MAP_SIZE]->getDescription() << endl;
        }
        //bot row
        for (int i=0;i<3;i++) {
            for (int j=0;j<5;j++) {
                map[(player.x-2+j) % MAP_SIZE][(player.y + 1) % MAP_SIZE]->printTexture(i);
            }
            //print whats in the directions
            switch(i) {
                case 0:
                    cout << "\033[0m\tEast: " << map[(player.x + 1) % MAP_SIZE][player.y % MAP_SIZE]->getDescription() << endl;
                    break;
                case 1:
                    cout << "\033[0m\tSouth: " << map[player.x % MAP_SIZE][(player.y + 1) % MAP_SIZE]->getDescription() << endl;
                    break;
                case 2:
                    cout << "\033[0m\tWest: " << map[(player.x - 1) % MAP_SIZE][player.y % MAP_SIZE]->getDescription() << endl;
                    break;
            }
        }

        cout << "Which way will you go? Enter N, E, S, or W:" << endl;
        char userInput;
        cin >> userInput;
        userInput = toupper(userInput);
        
        //make sure a direction was clarified
        while (userInput!='N' && userInput!='S' && userInput!='E' && userInput!='W') {
            cout << "INVALID RESPONSE: Enter N, E, S, or W:" << endl;
            cin >> userInput;
            userInput = toupper(userInput);
        }
        
        switch(toupper(userInput)){
            case 'N':
                player.y = player.y - 1;
                break;
            case 'E':
                player.x = player.x + 1;
                break;
            case 'S':
                player.y = player.y + 1;
                break;
            case 'W':
                player.x = player.x - 1;
                break;
        }

        //basically clear the screen
        ClearScreen();

        cout << map[player.x % MAP_SIZE][player.y % MAP_SIZE]->visit(player) << endl;

        if (!EndTheGame) {
            //player turn
            player.takeTurn();
    
            //loop the player from map coordinate MAP_SIZE to 2xMAP_SIZE so that the gui doesnt break with a weird negative modulus
            if (player.x < MAP_SIZE) {
                player.x += MAP_SIZE;
            } else if (player.x > MAP_SIZE*2) {
                player.x -= MAP_SIZE;
            }
    
            if (player.y < MAP_SIZE) {
                player.y += MAP_SIZE;
            } else if (player.y > MAP_SIZE*2) {
                player.y -= MAP_SIZE;
            }
        }
    }

    //if entered the hideout...
    if (EndTheGame) {
        if (player.getWeapon() < 2) {
            usleep(1000000);
            
            //slowly print this out ominously
            SlowPrint("\"HAHAHAHAAHAA YOU THOUGHT YOU COULD DEFEAT ME WITHOUT A WEAPON?!?!?\"");
            usleep(1000000);
        } else {
            //slowly print this out ominously
            SlowPrint("\"Ah... so, it's you...");
            usleep(1000000);
            
            SlowPrint(" Your ilk have done naught but destroy... and you have been too dense to see it.\"");
            usleep(2000000);
            
            ClearScreen();
            
            SlowPrint("\"I see you bring a weapon... BUT YOU ARE NO MATCH FOR ME");
            usleep(1000000);
            
            SlowPrint(" I SHALL TAKE YOUR HEAD AS UNDENIABLE PROOF OF THE WEAKNESS OF THE RULING CLASS");
            usleep(1000000);
            
            SlowPrint(" AND SEND MY FORCES OUT TO FINISH THIS REVOLUTION ONCE AND FOR ALL!\"");
            usleep(3000000);
            
            fightEnemy(player, "RABID PLEBIAN");
            
            if (player.isAlive()) {
                ClearScreen();
                
                usleep(1000000);
                SlowPrint("You defeated that pleb and then killed all the other terrorists,\nleaving countless towns and villages in ruin and drenched in the blood of the enemy.");
                usleep(1000000);
                SlowPrint("Everyone in the kingdom was happy...\nor, at least, you were.");
                usleep(1000000);
                SlowPrint("And then you lived a long, happy life until finally...");
                usleep(1000000);
            }
        }
    }
    cout << "You died." << endl;
    cout << "Your score: " << player.getScore() << endl;

    return 0;
}




//FIGHTEnemy
void fightEnemy(Player& p, string enemy) {
    int bearHealth = 5;
    string PlayerFrames[5][5];

    //if has sword set to this
    switch (p.getWeapon()) {
        case 0:
            // [0] [0-4] is neutral
            PlayerFrames[0][0] = "            ";
            PlayerFrames[0][1] = "     O      ";
            PlayerFrames[0][2] = "   ——|——    ";
            PlayerFrames[0][3] = "     |      ";
            PlayerFrames[0][4] = "    / \\     ";
            // [1] [0-4] is readying attack
            PlayerFrames[1][0] = "            ";
            PlayerFrames[1][1] = "    O       ";
            PlayerFrames[1][2] = "    |\\/     ";
            PlayerFrames[1][3] = "    |       ";
            PlayerFrames[1][4] = "    /\\      ";
            // [2] [0-4] is attack
            PlayerFrames[2][0] = "            ";
            PlayerFrames[2][1] = "     -∘O    ";
            PlayerFrames[2][2] = "    -</———— ";
            PlayerFrames[2][3] = "     /      ";
            PlayerFrames[2][4] = "    / \\     ";
            // [3] [0-4] is stand after attack
            PlayerFrames[3][0] = "            ";
            PlayerFrames[3][1] = "       O    ";
            PlayerFrames[3][2] = "     </———  ";
            PlayerFrames[3][3] = "     /      ";
            PlayerFrames[3][4] = "    / \\     ";
            // [4] [0-4] is going back to neutral
            PlayerFrames[4][0] = "            ";
            PlayerFrames[4][1] = "     O∘-    ";
            PlayerFrames[4][2] = "   ——|——-   ";
            PlayerFrames[4][3] = "     |      ";
            PlayerFrames[4][4] = "    / \\     ";
            break;
        case 1:
            // [0] [0-4] is neutral
            PlayerFrames[0][0] = "        |   ";
            PlayerFrames[0][1] = "     O  |   ";
            PlayerFrames[0][2] = "   ——|——|   ";
            PlayerFrames[0][3] = "     |      ";
            PlayerFrames[0][4] = "    / \\     ";
            // [1] [0-4] is readying attack
            PlayerFrames[1][0] = "          / ";
            PlayerFrames[1][1] = "     O   /  ";
            PlayerFrames[1][2] = "   ——|——/   ";
            PlayerFrames[1][3] = "     |      ";
            PlayerFrames[1][4] = "    / \\     ";
            // [2] [0-4] is attack
            PlayerFrames[2][0] = "            ";
            PlayerFrames[2][1] = "     O      ";
            PlayerFrames[2][2] = "   ——|——\\   ";
            PlayerFrames[2][3] = "     |   \\)|";
            PlayerFrames[2][4] = "    / \\   \\/";
            // [3] [0-4] is stick down
            PlayerFrames[3][0] = "            ";
            PlayerFrames[3][1] = "     O      ";
            PlayerFrames[3][2] = "   ——|——\\   ";
            PlayerFrames[3][3] = "     |   \\  ";
            PlayerFrames[3][4] = "    / \\   \\ ";
            // [4] [0-4] is stick going back up
            PlayerFrames[4][0] = "        |\\  ";
            PlayerFrames[4][1] = "     O  | \\ ";
            PlayerFrames[4][2] = "   ——|——| ))";
            PlayerFrames[4][3] = "     |      ";
            PlayerFrames[4][4] = "    / \\     ";
            break;
        case 2:
            // [0] [0-4] is neutral
            PlayerFrames[0][0] = "        |   ";
            PlayerFrames[0][1] = "     O _|_  ";
            PlayerFrames[0][2] = "   ——|——|   ";
            PlayerFrames[0][3] = "     |      ";
            PlayerFrames[0][4] = "    / \\     ";
            // [1] [0-4] is readying attack
            PlayerFrames[1][0] = "          / ";
            PlayerFrames[1][1] = "     O  \\/  ";
            PlayerFrames[1][2] = "   ——|——/\\  ";
            PlayerFrames[1][3] = "     |      ";
            PlayerFrames[1][4] = "    / \\     ";
            // [2] [0-4] is attack
            PlayerFrames[2][0] = "            ";
            PlayerFrames[2][1] = "     O      ";
            PlayerFrames[2][2] = "   ——|——\\/  ";
            PlayerFrames[2][3] = "     |  /\\)|";
            PlayerFrames[2][4] = "    / \\   \\/";
            // [3] [0-4] is sword down
            PlayerFrames[3][0] = "            ";
            PlayerFrames[3][1] = "     O      ";
            PlayerFrames[3][2] = "   ——|——\\/  ";
            PlayerFrames[3][3] = "     |  /\\  ";
            PlayerFrames[3][4] = "    / \\   \\ ";
            // [4] [0-4] is sword going back up
            PlayerFrames[4][0] = "        |\\  ";
            PlayerFrames[4][1] = "     O _|_\\ ";
            PlayerFrames[4][2] = "   ——|——| ))";
            PlayerFrames[4][3] = "     |      ";
            PlayerFrames[4][4] = "    / \\     ";
            break;
    }
    string EnemyFrames[4][5] = {
        { // [0] [0-4] is neutral
            "",
            " _.^-________",
            "¯---,_______,_)",
            "    | /    / /",
            "   /      /"
        },
        { // [1] [0-4] is ready attack
            "",
            "   ▴_",
            "-¯' ,¯¯¯¯¯¯¯¯¯¯\\",
            " ¯¯/—————————/—'",
            "   \\        /"
        },
        { // [2] [0-4] is attack
            "     _.^-__",
            "    ¯---,__———",
            "    —¯¯¯ / ———,_)",
            "             / /",
            "            /"
        },
        { // [3] [0-4] is dead
            "",
            "    |       |",
            " ___|—'—————|—|",
            "¯-x  _________)",
            "   v¯"
        }
    };

    if (enemy == "DOG") {
        //if it dog, give it tail
        EnemyFrames[0][2] += "—-";
        EnemyFrames[1][2] += "__";
        EnemyFrames[2][2] += "—-";
        EnemyFrames[3][3] += "—-";
    } else if (enemy == "MORTAL PLEBIAN") {
        // [0] [0-4] is neutral
        EnemyFrames[0][0] = "";
        EnemyFrames[0][1] = "  ('_')";
        EnemyFrames[0][2] = "   _|_";
        EnemyFrames[0][3] = "    |";
        EnemyFrames[0][4] = "   / \\";
        // [1] [0-4] is ready attack
        EnemyFrames[1][0] = "";
        EnemyFrames[1][1] = "";
        EnemyFrames[1][2] = "  ('_')";
        EnemyFrames[1][3] = "   —|—";
        EnemyFrames[1][4] = "  __|__";
        // [2] [0-4] is attack
        EnemyFrames[2][0] = "(>o<)";
        EnemyFrames[2][1] = "   \\/";
        EnemyFrames[2][2] = "   /\\_";
        EnemyFrames[2][3] = "    /";
        EnemyFrames[2][4] = "";
        // [3] [0-4] is dead
        EnemyFrames[3][0] = "";
        EnemyFrames[3][1] = "";
        EnemyFrames[3][2] = "    (x_x)";
        EnemyFrames[3][3] = "    —/—";
        EnemyFrames[3][4] = "  __/__";
    } else if (enemy == "SEA MONSTER") {
        bearHealth = 10;
        // [0] [0-4] is neutral
        EnemyFrames[0][0] = "       /¯¯\\";
        EnemyFrames[0][1] = "      /O  /";
        EnemyFrames[0][2] = "   | |   /";
        EnemyFrames[0][3] = " |  \\| ||    |";
        EnemyFrames[0][4] = " \\__/ / /\\__/";
        // [1] [0-4] is ready attack
        EnemyFrames[1][0] = "        ___ ";
        EnemyFrames[1][1] = "       /o _|";
        EnemyFrames[1][2] = "    / /  /";
        EnemyFrames[1][3] = "   /|/ ||    |";
        EnemyFrames[1][4] = "   \\/ / /\\__/";
        // [2] [0-4] is attack
        EnemyFrames[2][0] = "   /¯¯\\";
        EnemyFrames[2][1] = "   \\O  \\";
        EnemyFrames[2][2] = "    \\   |";
        EnemyFrames[2][3] = "  ——_| ||    |";
        EnemyFrames[2][4] = "——__/ / /\\__/";
        // [3] [0-4] is dead
        EnemyFrames[3][0] = "";
        EnemyFrames[3][1] = "";
        EnemyFrames[3][2] = "  ___————___";
        EnemyFrames[3][3] = " / / ,    X \\";
        EnemyFrames[3][4] = "__/ /\\_,____ \\";
    } else if (enemy == "RABID PLEBIAN") {
        bearHealth = 12;
        // [0] [0-4] is neutral
        EnemyFrames[0][0] = "        _";
        EnemyFrames[0][1] = "    \033[33m\\\033[0m  (_)";
        EnemyFrames[0][2] = "     \033[33m\\/\033[0m/|\\";
        EnemyFrames[0][3] = "     \033[33m/\\\033[0m|||";
        EnemyFrames[0][4] = "       / \\";
        // [1] [0-4] is ready attack
        EnemyFrames[1][0] = "         _";
        EnemyFrames[1][1] = "        (_)";
        EnemyFrames[1][2] = "    \033[33m___|_\033[0m/>";
        EnemyFrames[1][3] = "       \033[33m|\033[0m//";
        EnemyFrames[1][4] = "       / \\";
        // [2] [0-4] is attack
        EnemyFrames[2][0] = "      _";
        EnemyFrames[2][1] = "\033[33m___|_\033[0m(_)";
        EnemyFrames[2][2] = "   \033[33m|\033[0m ¯¯\\>";
        EnemyFrames[2][3] = "        \\";
        EnemyFrames[2][4] = "       / \\";
        // [3] [0-4] is dead
        EnemyFrames[3][0] = "";
        EnemyFrames[3][1] = "";
        EnemyFrames[3][2] = "";
        EnemyFrames[3][3] = "  __      __";
        EnemyFrames[3][4] = "  __>——|—|_X|";
    }
    
    for (int i=0;i<2;i++) {
        ClearScreen();
        cout << "\t\033[31m" << enemy << " ATTACK\033[0m\n\n" << endl;
        usleep(500000);
        ClearScreen();
        cout << "\t" << enemy << " ATTACK\n\n" << endl;
        usleep(500000);
    }
    
    //emergency flee bool if u dont want to fite
    bool flee = false;
    while (p.isAlive() && bearHealth > 0 && !flee) {
        string input;
        int selectedNum = 2147483632;

        //select option screen
        while (selectedNum < 1 || selectedNum > 4) {
            //clear screen
            ClearScreen();

            //display scene
            cout << "\033[97;41mFIGHT\033[0m" << endl
                << p.barHealth()
                << "\033[0m\n" << endl;
            for (int i=0;i<5;i++) cout << PlayerFrames[0][i] << EnemyFrames[0][i] << endl;
            cout << "             " << enemy << " HP: \033[1;43m";
            for (int i = 0; i < bearHealth ; i++) cout << "/";
            cout << endl;

            //give player options and wait for input
            cout << "\033[0mEnter \033[44m(1) normal attack\033[0m, \033[1;41m(2) poke eyes[risky]\033[0m, \033[42m(3) run away\033[0m, \033[46m(4) help\033[0m" << endl;
            
            if (selectedNum != 2147483632) {
                cout << "ERROR invalid input. Please input \033[44m\"1\"\033[0m, \033[1;41m\"2\"\033[0m, \033[42m\"3\"\033[0m, or \033[46m\"4\"\033[0m" << endl;
            }
            
            cin >> input;

            selectedNum = atoi(input.c_str());
        }
        
        //show help thing if requested
        if (selectedNum == 4) {
            cout << "1. \033[44mNormal Attack\033[0m. Does " << p.getWeapon()*2+1 << " damage with your current weapon.\n" << endl;
            cout << "2. \033[1;41mPoke Eyes\033[0m. Guaranteed " << 2*(p.getWeapon()*2+1) << " damage with your current weapon.\n\t60\% chance that the enemy's turn will occur both before and after yours\n" << endl;
            cout << "3. \033[42mRun\033[0m. Allows you to escape, but uses 1 hunger and 1 thirst\n" << endl;
            
            cin >> input;
            selectedNum = atoi(input.c_str());
        }

        // play out the selected thing
        switch (selectedNum) {
            case 2:
                if (rand() % 100 > 40) {
                    //enemy attack [it goes up then down]
                //extra brackets to limit the scope of bool up
                {bool up = true;
                for (int j=0;j>-1 && bearHealth > 0;) {
                    //clear screen
                    ClearScreen();

                    //display scene
                    cout << "\033[97;41mFIGHT\033[0m" << endl
                        << p.barHealth()
                        << "\033[0m\n" << endl;
                    for (int i=0;i<5;i++) cout << PlayerFrames[0][i] << EnemyFrames[j][i] << endl;
                    cout << "             " << enemy << " HP: \033[1;43m";
                    for (int i = 0; i < bearHealth ; i++) cout << "/";
                        cout << "\033[0m" << endl;
                    usleep(100000);

                    //enemy goes up and then back down
                    if (up) {
                        if (j==2) {
                            j--;
                            up = false;
                            usleep(300000);
                            p.takeDamage(1);
                            
                            //boss does more damage
                            if (enemy == "RABID PLEBIAN") p.takeDamage(1);
                        } else j++;
                    } else {
                        j--;
                    }
                }}
                }
            case 1:
                //player attack
                for (int j=1;j<5;j++) {
                    //clear screen
                    ClearScreen();

                    //display scene
                    cout << "\033[97;41mFIGHT\033[0m" << endl
                        << p.barHealth()
                        << "\033[0m\n" << endl;
                    for (int i=0;i<5;i++) cout << PlayerFrames[j][i] << EnemyFrames[0][i] << endl;
                    cout << "             " << enemy << " HP: \033[1;43m";
                    for (int i = 0; i < bearHealth ; i++) cout << "/";
                        cout << "\033[0m" << endl;
                    usleep(100000);

                    if (j == 3) {
                        usleep(300000);
                        bearHealth -= selectedNum*(1+(p.getWeapon()*2));
                    }
                }
                
                //clear screen
                ClearScreen();

                //display scene
                cout << "\033[97;41mFIGHT\033[0m" << endl
                    << p.barHealth()
                    << "\033[0m\n" << endl;
                for (int i=0;i<5;i++) cout << PlayerFrames[0][i] << EnemyFrames[0][i] << endl;
                cout << "             " << enemy << " HP: \033[1;43m";
                for (int i = 0; i < bearHealth ; i++) cout << "/";
                cout << "\033[0m" << endl;
                usleep(300000);

                //enemy attack [it goes up then down]
                //extra brackets to limit the scope of bool up
                {bool up = true;
                for (int j=0;j>-1 && bearHealth > 0;) {
                    //clear screen
                    ClearScreen();

                    //display scene
                    cout << "\033[97;41mFIGHT\033[0m" << endl
                        << p.barHealth()
                        << "\033[0m\n" << endl;
                    for (int i=0;i<5;i++) cout << PlayerFrames[0][i] << EnemyFrames[j][i] << endl;
                    cout << "             " << enemy << " HP: \033[1;43m";
                    for (int i = 0; i < bearHealth ; i++) cout << "/";
                    cout << "\033[0m" << endl;
                    usleep(100000);

                    //enemy goes up and then back down
                    if (up) {
                        if (j==2) {
                            j--;
                            up = false;
                            usleep(300000);
                            p.takeDamage(1);
                            
                            //boss does more damage
                            if (enemy == "RABID PLEBIAN") p.takeDamage(1);
                        } else j++;
                    } else {
                        j--;
                    }
                }}
                break;
            case 3:
                ClearScreen();
                if (enemy == "RABID PLEBIAN") {
                    for (int i=0;i<5;i++) {
                        ClearScreen();
                        cout << "\033[31mYou cannot flee from this battle!\033[0m" << endl;
                        usleep(300000);
                        ClearScreen();
                        cout << "You cannot flee from this battle!" << endl;
                        usleep(300000);
                    }
                    usleep(300000);
                } else for (string input = "";input!="N"&&input!="n"&&!flee;) {
                    cout << "Are you sure you wish to flee? (Y/N)\nIt will consume 1 hunger and 1 thirst" << endl;
                    cout << p.barHunger() << endl << p.barThrist() << "\033[0m" << endl;
                    
                    cin >> input;
                    if (input.length() > 1) {
                        input = input.at(0);
                    }
                    
                    if (input=="Y" || input=="y") {
                        p.increaseHunger(-1);
                        p.increaseThrist(-1);
                        flee = true;
                    }
                }
                break;
        }
    }

    //victory message
    if (bearHealth <= 0) {
        //clear screen
        ClearScreen();

        //display scene
        cout << "\033[97;41mFIGHT\033[0m" << endl
            << p.barHealth()
            << "\033[0m\n" << endl;
        for (int i=0;i<5;i++) cout << PlayerFrames[0][i] << "\033[31m" << EnemyFrames[3][i] << "\033[0m" << endl;
        cout << "YOU DEFEATED THE " << enemy << ", ATE ITS FLESH AND DRANK ITS BLOOD" << endl;
        usleep(2000000);
        cout << "\t\tVICTORY" << endl;
        p.increaseHunger(5);
        p.increaseThrist(2);
        usleep(3000000);

        //clear screen
        ClearScreen();
    }
}
