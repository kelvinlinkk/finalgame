#pragma once
#ifndef PARTY_H
#define PARTY_H
#include <string>
#include <vector>

#include "character.h"
class Party {
   private:
    std::string partyname;
    std::shared_ptr<Character> warrior, fighter, mage;

   public:
    bool isAlive;
    Party(std::string, std::string, std::string, std::string);
    void getINFO() const;
    void partyHeal(std::string, int);
    void partyHurt(std::string, int);
    void partyRecover(std::string, int);
    int partyCast(std::string, int);
    int partyAttack();
};
#endif
