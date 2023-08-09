#include "player.h"

using namespace std;

void ClearScreen() {
    cout << "\033[2J\033[3J" << endl;
}

//player class
Player::Player(int x, int y){
    health = MAX_HEALTH;
    hunger = MAX_HUNGER;
    thirst = MAX_THIRST;

    this->x = x;
    this->y = y;
    this->score = 0;
    this->weapon = 0;
}

int Player::getScore() const {
    return score;
}

int Player::getWeapon() const {
    return weapon;
}

void Player::takeDamage(int val){
    this->health -= val;
    if(this->health < 0) this->health = 0;
}

void Player::takeTurn(){
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

string Player::barHealth() const {
    stringstream ss;
    ss << "\033[0mHealth: \033[1;41m";
    for (int i = 0; i < this->health; i++) ss << "|";
    return ss.str();
}

string Player::barHunger() const {
    stringstream ss;
    ss << "\033[0mHunger: \033[1;43m";
    for (int i = 0; i < this->hunger; i++) ss << "|";
    return ss.str();
}

string Player::barThrist() const {
    stringstream ss;
    ss << "\033[0mThrist: \033[1;44m";
    for (int i = 0; i < this->thirst; i++) ss << "|";
    return ss.str();
}

string Player::barWeapon() const {
    string wep = "\t\033[0mCurrent Weapon: \033[1;100m";
    switch(weapon) {
        case 0: wep += "✊\033[0m"; break;
        case 1: wep += "\033[33m\\\033[0m"; break;
        case 2: wep += "🗡\033[0m️"; break;
    }

    return wep;
}

bool Player::foundWeapon(int newType) {
    //if have better then say false so that it doesnt say every time you find a weapon
    if (weapon >= newType) return false;

    //set the weapon and return true that it has been upgraded
    weapon = newType;
    return true;
}

bool Player::isAlive() const {
    return this->health > 0;
}

void Player::increaseThrist(int val){
    this->thirst += val;
    if(this->thirst > MAX_THIRST) this->thirst = MAX_THIRST+1;//+1 because it immediately goes down 1
}

void Player::increaseHunger(int val){
    this->hunger += val;
    if(this->hunger > MAX_HUNGER) this->hunger = MAX_HUNGER+1;//+1 because it immediately goes down 1
}

void Player::heal(int helth) {
    health += helth;
    if (health > MAX_HEALTH) {
        health = MAX_HEALTH;
    }
}

void Player::ArriveAtHideout() {
    EndTheGame = true;
}

bool Player::HasReachedHideout() const {
    return EndTheGame;
}

//FIGHTENEMY
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
        EnemyFrames[1][3] = "   /|/  |/    /";
        EnemyFrames[1][4] = "   \\/  //\\__/";
        // [2] [0-4] is attack
        EnemyFrames[2][0] = "   /¯¯\\";
        EnemyFrames[2][1] = "   \\O  \\";
        EnemyFrames[2][2] = "    \\   |";
        EnemyFrames[2][3] = "  ——\\|  | ¯\\";
        EnemyFrames[2][4] = "——__/ \\ /\\_/";
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

                        //clear screen
                        ClearScreen();
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
