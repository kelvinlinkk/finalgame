#include<string>
#include"weapon.h"

Weapon::Weapon(std::string name):name(name), lvl(1){};
std::string Weapon::getName() const{
    return this->name;
}
int Weapon::getlvl() const{
    return this->lvl;
}
void Weapon::upgrade(){
    this->lvl++;
    return;
}