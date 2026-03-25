#pragma once
#ifndef WEAPON_H
#define WEAPON_H
#include<string>
class Weapon{
private:
    std::string name;    
public:
    Weapon();
    Weapon(std::string);
    std::string getName();
};
#endif