#pragma once
#ifndef PARTY_H
#define PARTY_H
#include<string>
#include<vector>
#include"character.h"
class Party{
    private:
        std::string name;
        Character& warrior, fighter, mage;    
    public:
        Party(std::string name, Character& warrior, Character& fighter, Character& mage) 
            :name(name), warrior(warrior),fighter(fighter), mage(mage){};
        void getINFO() const;
        void heal(std::string, int);
        void hurt(std::string, int);
        void recover(std::string, int);
        void cast(std::string, int);
        void attack();
};
#endif