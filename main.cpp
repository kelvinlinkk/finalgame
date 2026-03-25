#include <iostream>
#include <string>

#include "character.h"
#include "command.h"
#include "weapon.h"

using namespace std;

int main() {
    
    
    string cmd = "";
    Weapon ax("Ax"), staff("Staff");
    Character  warrior("Warrior", 150, 20, 30, ax), mage("Mage", 70, 100, 10, staff);
    
    int hp, mp, atk;
    string cname, wname;
    cout<<"Create your Hero(Name HP MP ATK):"<<endl;
    cin>>cname>>hp>>mp>>atk;
    cout<<"Equip a weapon:"<<endl;
    cin>>wname;
    Weapon *myWeapon=new Weapon(wname);
    Character *mainChar = new Character(cname, hp,mp,atk,*myWeapon);
    mainChar->INFO();
    warrior.INFO();
    mage.INFO();
    getline(cin, cmd);
    while (getline(cin, cmd)) {
        if (!GameSystem::handlingCommand(*mainChar, cmd)) {
            break;
        }
    }
    delete mainChar;
    delete myWeapon;
    return 0;
}