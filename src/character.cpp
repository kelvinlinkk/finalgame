#include "character.h"

#include <iostream>
#include <string>
#include<memory>
#include "weapon.h"

// constructors/destructors
Character::Character()
    : name("untitiled"), hp(100), mp(100), atk(0), weapon(nullptr) {};
Character::Character(std::string name, int hp, int mp, int atk,
                     std::string weaponName) {
    setINFO(name, hp, mp, atk);
    this->weapon=std::make_unique<Weapon>(weaponName);
}
Character::~Character() {}

// character status
void Character::getINFO() const {
    std::cout << "-Character:" << getName() << std::endl;
    if(hasHP()){   
    std::cout << "--HP:" << getHP() << std::endl;
    std::cout << "--MP:" << getMP() << std::endl;
    std::cout << "--ATK:" << getATK() << std::endl;
    std::cout << "--Weapon:" << this->weapon->getName() << std::endl;
    }else{
        std::cout <<"--"<< getName()<<" is dead."<<std::endl;
    }
}
void Character::setINFO(std::string name, int hp, int mp, int atk) {
    setName(name);
    setHP(hp);
    setMP(mp);
    setATK(atk);
}

bool Character::hasHP() const { return (getHP() > 0); }
bool Character::hasMP() const { return (getMP() > 0); }

// get stats
std::string Character::getName() const { return this->name; }
int Character::getHP() const { return this->hp; }
int Character::getMP() const { return this->mp; }
int Character::getATK() const { return this->atk; }

// set stats
std::string Character::setName(std::string name) {
    this->name = name;
    return this->name;
}
int Character::setHP(int hp) {
    this->hp = (hp < 0) ? 0 : hp;
    return this->hp;
}
int Character::setMP(int mp) {
    this->mp = (mp < 0) ? 0 : mp;

    if (!hasMP()) {
        this->mp = 0;
    }

    return this->mp;
}
int Character::setATK(int atk) {
    this->atk = atk;
    return this->atk;
}

// basic operations
void Character::heal(int hp) {
    if (hp >= 0) setHP(getHP() + hp);
    std::cout <<"-"<< this->getName()<< " HP:" << getHP() << std::endl;
}

void Character::recover(int mp) {
    if (!hasHP()) {
        std::cout <<"-"<< this->getName()<<" is dead." << std::endl;
        return;
    } else {
        if (mp >= 0) setMP(getMP() + mp);
        std::cout <<"-"<< this->getName()<< " MP:" << getMP() << std::endl;
    }
}

void Character::hurt(int hp) {
    if (!hasHP()) {
        std::cout <<"-"<< this->getName()<<" is dead." << std::endl;
        return;
    }

    if (hp >= 0) setHP(getHP() - hp);

    if (!hasHP()) {
        std::cout <<"-"<< this->getName()<<" is dead." << std::endl;
    } else {
        std::cout <<"-"<< this->getName()<< " HP:" << getHP() << std::endl;
    }
}

// attacks
int Character::cast(int mp) {
    if (!hasHP()) {
        std::cout <<"-"<< this->getName()<<" is dead." << std::endl;
        return 0;
    }

    if (getMP() < mp) {
        std::cout <<"-"<< this->getName()<< " not enough MP." << std::endl;
        return 0;
    }

    if (mp >= 0) setMP(getMP() - mp);
    std::cout <<"-"<< this->getName()<< " MP:" << getMP() << std::endl;
    return getMP() * 0.5;
}
int Character::attack() {
    if (!hasHP()) {
        std::cout <<"-"<< this->getName()<<" is dead." << std::endl;
        return 0;
    }
    std::cout <<"-"<< this->getName() << " attacks with "
              << (this->weapon)->getName() << "! "<< "ATK:" << getATK() << std::endl;
    return getATK();
}
