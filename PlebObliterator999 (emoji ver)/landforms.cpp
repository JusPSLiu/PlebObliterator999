#include "landforms.h"
#include "player.h"

void Land::printTexture(int row) {
    if (row < 3) {
        //if row is 0 1 or 2 then dont have to insert player in center
        cout << texture[row];
    } else {
        //if row is 3, 4 or 5 that means player there. texture[3] has the player
        if (row == 4) cout << texture[3];
        else cout << texture[row-3];
    }
}

//Forest functions
Forest::Forest() {
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

string Forest::getDescription(){
    return "a densely wooded forest";
}

string Forest::visit(Player& player){
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

//Lake functions
Lake::Lake() {
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

string Lake::getDescription(){
    return "a clear sparkling lake";
}

string Lake::visit(Player& player){
    player.increaseThrist(2);

    int randomNum = rand() % 100;
    if (randomNum > 75) {
        fightEnemy(player, "SEA MONSTER");
        return "You were attacked by a sea monster while on your boat";
    }
    return "You take a boat onto the lake and drink its clean water";
}

//Plain functions
Plain::Plain() {
    //randomize texture
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

string Plain::getDescription(){
    return "an open field";
}

string Plain::visit(Player& player){
    if (rand() % 100 > 85) {
        fightEnemy(player, "COW");
        return "You were attacked by a cow";
    }
    return "You relax and sit there";
}

//Town functions
Town::Town() {
    //randomize texture
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

string Town::getDescription(){
    return "a town";
}

string Town::visit(Player& player){
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

//Desert functions
Desert::Desert() {
    //randomize texture
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

string Desert::getDescription(){
    return "a desert";
}

string Desert::visit(Player& player){
    if (rand() % 10 > 7) {
        player.increaseThrist(2);
        player.increaseHunger(3);
        return "You found a dead guy's supplies and feel revitalized";
    }
    player.increaseThrist(-1);
    return "You are now really dry and thirsty";
}

//WeaponStorageFacility functions
WeaponStorageFacility::WeaponStorageFacility() {
    //set the texture
    texture[0] = "\033[1;32;42m▒▓▒▓▒▓";
    texture[1] = "\033[1;32;42m▓\033[1;37;100m▒🗡️▓\033[1;32;42m▒";
    texture[2] = "\033[1;32;42m▒▓▒▓▒▓";
    texture[3] = "\033[1;32;42m▓\033[1;37;100m▒😐▓\033[1;32;42▒";
}

string WeaponStorageFacility::getDescription(){
    return "the secret rebel weapon storage facility";
}

string WeaponStorageFacility::visit(Player& player){
    if (player.foundWeapon(2))
        return "You found a sword in the rebel weapon storage facility and are now prepared to quell the insurgency";
    return "There's nothing more to do here.";
}

//SecretRebellionHideout functions
SecretRebellionHideout::SecretRebellionHideout() {
    //set the texture
    texture[0] = "\033[1;31;41m▒▓▒▓▒▓";
    texture[1] = "\033[1;31;41m▓\033[1;37;100m▒▓▒▓\033[1;31;41m▒";
    texture[2] = "\033[1;31;41m▒▓▒▓▒▓";
    texture[3] = "\033[1;31;41m▓\033[1;37;100m▒😐▓\033[1;31;41m▒";
}

string SecretRebellionHideout::getDescription( ){
    return "BloodRed Secret Hideout. You should only enter after you obtain a sword.";
}

string SecretRebellionHideout::visit(Player& player){
    player.ArriveAtHideout();
    return "You enter the rebellion hideout, and are greeted by a vaguely familiar voice.";
}
