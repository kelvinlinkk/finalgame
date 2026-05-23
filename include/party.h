#pragma once
#ifndef PARTY_H
#define PARTY_H
#include <string>
#include <vector>

#include "character.h"
class Party {
   private:
    std::string partyname;
    std::shared_ptr<Hero> hero;
    std::shared_ptr<Warrior> warrior;
    std::shared_ptr<Mage> mage;


   public:
    bool isAlive;
    Party(std::string, std::string, std::string, std::string);
    void getINFO() const;
    void partyHeal(std::string, int);
    void partyHurt(std::string, int);
    void partyRecover(std::string, int);
    int partyCast(std::string);
    int partyAttack();
    void partyUpgrade(std::string);
    void memberaction(std::shared_ptr<Character>);
    void partyEquip(std::string, std::string);
};
#endif
