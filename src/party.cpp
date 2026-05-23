#include "party.h"

#include <iostream>
#include <string>
#include <vector>

#include "character.h"

void Party::getINFO() const {
    std::cout << "Party name: " << this->partyname << std::endl
              << *hero << *warrior << *mage;
};
Party::Party(std::string partyname, std::string heroname,
             std::string warriorname, std::string magename)
    : partyname(partyname), isAlive(true) {
    this->hero = std::make_shared<Hero>(heroname, 100, 50, 20, "sword");
    this->warrior = std::make_shared<Warrior>(warriorname, 150, 20, 30, "axe"),
    this->mage = std::make_shared<Mage>(magename, 70, 100, 10, "staff");
};
void Party::partyHeal(std::string name, int num) {
    if (name == "all") {
        hero->heal(num);
        warrior->heal(num);
        mage->heal(num);
    } else {
        if (name == hero->getName()) {
            hero->heal(num);
            return;
        }
        if (name == warrior->getName()) {
            warrior->heal(num);
            return;
        }
        if (name == mage->getName()) {
            mage->heal(num);
            return;
        }
        std::cout << "Invalid input." << std::endl;
    }
};

void Party::partyHurt(std::string name, int num) {
    if (name == "all") {
        hero->hurt(num);
        warrior->hurt(num);
        mage->hurt(num);
        isAlive = hero->hasHP() || warrior->hasHP() || mage->hasHP();
    } else {
        if (name == hero->getName()) {
            hero->hurt(num);
            isAlive = hero->hasHP() || warrior->hasHP() || mage->hasHP();
            return;
        }
        if (name == warrior->getName()) {
            warrior->hurt(num);
            isAlive = hero->hasHP() || warrior->hasHP() || mage->hasHP();
            return;
        }
        if (name == mage->getName()) {
            mage->hurt(num);
            isAlive = hero->hasHP() || warrior->hasHP() || mage->hasHP();
            return;
        }
        std::cout << "Invalid input." << std::endl;
    }
    isAlive = hero->hasHP() || warrior->hasHP() || mage->hasHP();
};

void Party::partyRecover(std::string name, int num) {
    if (name == "all") {
        hero->recover(num);
        warrior->recover(num);
        mage->recover(num);
    } else {
        if (name == hero->getName()) {
            hero->recover(num);
            return;
        }
        if (name == warrior->getName()) {
            warrior->recover(num);
            return;
        }
        if (name == mage->getName()) {
            mage->recover(num);
            return;
        }
        std::cout << "Invalid input." << std::endl;
    }
};

int Party::partyCast(std::string name) {
    int cast = 0;
    if (name == "all") {
        cast += hero->cast();
        cast += warrior->cast();
        cast += mage->cast();
    } else {
        if (name == hero->getName()) {
            cast += hero->cast();
            return cast;
        }
        if (name == warrior->getName()) {
            cast += warrior->cast();
            return cast;
        }
        if (name == mage->getName()) {
            cast += mage->cast();
            return cast;
        }
        std::cout << "Invalid input." << std::endl;
    }
    return cast;
};

int Party::partyAttack() {
    int atk = 0;
    if (hero->hasHP()) atk += hero->attack();
    if (warrior->hasHP()) atk += warrior->attack();
    if (mage->hasHP()) atk += mage->attack();
    return atk;
}

void Party::partyUpgrade(std::string name) {
    if (name == "all") {
        ++(*hero);
        ++(*warrior);
        ++(*mage);
    } else {
        if (name == hero->getName()) {
            ++(*hero);
            return;
        }
        if (name == warrior->getName()) {
            ++(*warrior);
            return;
        }
        if (name == mage->getName()) {
            ++(*mage);
            return;
        }
        std::cout << "Invalid input." << std::endl;
    }
    return;
};

void Party::partyEquip(std::string name, std::string wname) {
    if (name == "all") {
        (*hero) += std::unique_ptr<Weapon>(new Weapon(wname));
        (*warrior) += std::unique_ptr<Weapon>(new Weapon(wname));
        (*mage) += std::unique_ptr<Weapon>(new Weapon(wname));
    } else {
        if (name == hero->getName()) {
            (*hero) += std::unique_ptr<Weapon>(new Weapon(wname));
            return;
        }
        if (name == warrior->getName()) {
            (*warrior) += std::unique_ptr<Weapon>(new Weapon(wname));
            return;
        }
        if (name == mage->getName()) {
            (*mage) += std::unique_ptr<Weapon>(new Weapon(wname));
            return;
        }
        std::cout << "Invalid input." << std::endl;
    }
    return;
};
void Party::memberaction(std::shared_ptr<Character> enemy) {
    if (hero->hasHP() && enemy->hasHP()) hero->action(enemy);
    if (warrior->hasHP() && enemy->hasHP()) warrior->action(enemy);
    if (mage->hasHP() && enemy->hasHP()) mage->action(enemy);
}
