#include<string>
#include"weapon.h"

Weapon::Weapon(std::string name):name(name){};
std::string Weapon::getName(){
    return this->name;
}