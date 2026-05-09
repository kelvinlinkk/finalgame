#pragma once
#ifndef WEAPON_H
#define WEAPON_H
#include<string>
class Weapon{
private:
    std::string name;
    int lvl;
public:
    Weapon(std::string);
    std::string getName() const;
    int getlvl() const;
    void upgrade();
};
#endif