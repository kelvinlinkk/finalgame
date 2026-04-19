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
    
    Character warrior(warriorname, 100, 50, 20, sword),
        fighter(fightername, 150, 20, 30, axe),
        mage(magename, 70, 100, 10, staff);
    Party party(partyname, warrior, fighter, mage);
    cout << "Input your action:" << endl;
    getline(cin, cmd);
    while (getline(cin, cmd)) {
        if (!handlingCommand(party, cmd)) {
            break;
        }
    }
    return 0;
}