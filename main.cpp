#include <iostream>
#include <string>

#include "character.h"
#include "gamemanager.h"
#include "party.h"
#include "weapon.h"

using namespace std;

int main() {
    string partyname, warriorname, fightername, magename;
    cout << "Create your party:" << endl;
    cin >> partyname >> warriorname >> fightername >> magename;

    gameManager game(partyname, warriorname, fightername, magename);
    game.startGame();
    return 0;
}
