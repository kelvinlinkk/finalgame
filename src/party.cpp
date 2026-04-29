#include "party.h"

#include <iostream>
#include <string>
#include <vector>

#include "character.h"

void Party::getINFO() const {
    std::cout << "Party name:" << this->partyname << std::endl;
    warrior->getINFO();
    fighter->getINFO();
    mage->getINFO();
};
Party::Party(std::string partyname, std::string warriorname,
             std::string fightername, std::string magename)
    : partyname(partyname), isAlive(true) {
    this->warrior =
        std::make_shared<Character>(warriorname, 100, 50, 20, "sword");
    this->fighter =
        std::make_shared<Character>(fightername, 150, 20, 30, "axe"),
    this->mage = std::make_shared<Character>(magename, 70, 100, 10, "staff");
};

void Party::partyHeal(std::string name, int num) {
    if (name == "all") {
        for (std::shared_ptr<Character> c : {warrior, fighter, mage}) {
            c->heal(num);
        }
    } else {
        for (std::shared_ptr<Character> c : {warrior, fighter, mage}) {
            if (name == c->getName()) {
                c->heal(num);
                return;
            }
        }
        std::cout << "Invalid input." << std::endl;
    }
};
void Party::partyHurt(std::string name, int num) {
    if (name == "all") {
        for (std::shared_ptr<Character> c : {warrior, fighter, mage}) {
            c->hurt(num);
            isAlive = warrior->hasHP();
        }
    } else {
        for (std::shared_ptr<Character> c : {warrior, fighter, mage}) {
            if (name == c->getName()) {
                c->hurt(num);
                isAlive = warrior->hasHP();
                return;
            }
        }
        std::cout << "Invalid input." << std::endl;
    }
};
void Party::partyRecover(std::string name, int num) {
    if (name == "all") {
        for (std::shared_ptr<Character> c : {warrior, fighter, mage}) {
            c->recover(num);
        }
    } else {
        for (std::shared_ptr<Character> c : {warrior, fighter, mage}) {
            if (name == c->getName()) {
                c->recover(num);
                return;
            }
        }
        std::cout << "Invalid input." << std::endl;
    }
};
int Party::partyCast(std::string name, int num) {
    int cast = 0;
    if (name == "all") {
        for (std::shared_ptr<Character> c : {warrior, fighter, mage}) {
            cast += c->cast(num);
        }
    } else {
        for (std::shared_ptr<Character> c : {warrior, fighter, mage}) {
            if (name == c->getName()) {
                cast += c->cast(num);
                return cast;
            }
        }
        std::cout << "Invalid input." << std::endl;
    }
    return cast;
};

int Party::partyAttack() {
    int atk = 0;
    for (std::shared_ptr<Character> c : {warrior, fighter, mage}) {
        atk += c->attack();
    }
    return atk;
}
