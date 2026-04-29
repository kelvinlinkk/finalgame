#include <iostream>
#include <string>

#include "character.h"
#include "weapon.h"
#include "party.h"
#include "gamesystem.h"

using namespace std;

int main() {
    string cmd = "";
    string partyname, warriorname, fightername, magename;
    Weapon sword("sword"),axe("axe"), staff("staff");
    cout << "Create your party:" << endl;
    cin >> partyname >> warriorname >> fightername >> magename;
    
    gameManager game(partyname, warriorname, fightername, magename);
    game.startGame();
    return 0;
}
