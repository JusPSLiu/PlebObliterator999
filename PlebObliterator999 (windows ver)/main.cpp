#include <iostream>
#include <time.h>
#include <unistd.h>
#include <cstring>
#include "landforms.h"

using namespace std;

//the MAP
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
        usleep(50000);
    }
    cout << endl;
}

void PrintDialogueSpace() {
    cout << "   " << flush;
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

    //OPENING CUTSCENE
    if (args <= 1 || strcmp(argv[1],"-skip") != 0) {
        ClearScreen();
        cout << "\n\n\n\n\n";
        PrintDialogueSpace();
        SlowPrint("Some random plebians are trying to overthrow the ruling class.");
        PrintDialogueSpace();
        usleep(1000000);
        SlowPrint("It's time to put them in their place.");
        PrintDialogueSpace();
        usleep(2000000);
        ClearScreen();
        cout << "\n\n\n\n\n";
        PrintDialogueSpace();
        usleep(1000000);
        SlowPrint("Their leader is hiding in the ");
        ClearScreen();

        cout << "\n\n";
        SecretRebellionHideout displayHideout;
        for (int i=0;i<3;i++) {
            cout << "\t\t\t\t\t";
            displayHideout.printTexture(i);
            cout << endl;
        }
        cout << "\033[0m";
        PrintDialogueSpace();
        cout << "Their leader is hiding in the \033[91m" << flush;
        SlowPrint("BloodRed Rebellion Hideout.");
        cout << "\033[0m" << flush;
        PrintDialogueSpace();

        usleep(1000000);
        SlowPrint("Nobody knows where it is, and all weapons have been taken.");
        PrintDialogueSpace();
        usleep(2000000);

        ClearScreen();
        cout << "\n\n\n\n\n";
        PrintDialogueSpace();
        SlowPrint("You must go and find the ");
        ClearScreen();

        cout << "\n\n";
        WeaponStorageFacility displayFacility;
        for (int i=0;i<3;i++) {
            cout << "\t\t\t\t\t";
            displayFacility.printTexture(i);
            cout << endl;
        }
        cout << "\033[0m";
        PrintDialogueSpace();
        cout << "You must go and find the \033[92m" << flush;
        SlowPrint("secret rebellion weapon facility");
        cout << "\033[0m" << flush;
        PrintDialogueSpace();

        usleep(1000000);
        SlowPrint("and grab a sword to destroy the rebel leader once and for all!");
        PrintDialogueSpace();
        usleep(2000000);
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
            PrintDialogueSpace();
            usleep(3500000);

            //slowly print this out ominously
            SlowPrint("\"HAHAHAHAAHAA YOU THOUGHT YOU COULD DEFEAT ME WITHOUT A WEAPON?!?!?\"");
            usleep(1000000);
        } else {
            //slowly print this out ominously
            PrintDialogueSpace();
            SlowPrint("\"Ah... so, it's you...");
            usleep(1000000);

            PrintDialogueSpace();
            SlowPrint(" Your ilk have done naught but destroy... and you have been too dense to percieve it.\"");
            usleep(2000000);

            ClearScreen();

            PrintDialogueSpace();
            SlowPrint("\"I see you bring a weapon... BUT YOU ARE NO MATCH FOR ME");
            usleep(1000000);

            PrintDialogueSpace();
            SlowPrint(" I SHALL TAKE YOUR HEAD AS UNDENIABLE PROOF OF THE WEAKNESS OF THE RULING CLASS");
            usleep(1000000);

            PrintDialogueSpace();
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

    usleep(10000000);
    return 0;
}
