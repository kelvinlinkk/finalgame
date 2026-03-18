#include "character.h"

#include <iostream>

// constructors/destructors
character::character() { setINFO(100, 100, 0); }
character::character(int hp, int mp, int atk) { setINFO(hp, mp, atk); }
character::~character() {}

// character status
void character::getINFO() const {
    std::cout << "HP:" << getHP() << std::endl;
    std::cout << "MP:" << getMP() << std::endl;
    std::cout << "ATK:" << getATK() << std::endl;
}
void character::setINFO(int hp, int mp, int atk) {
    setHP(hp);
    setMP(mp);
    setATK(atk);
}

bool character::hasHP() const { return (getHP() > 0); }
bool character::hasMP() const { return (getMP() > 0); }

// get stats
int character::getHP() const { return this->hp; }
int character::getMP() const { return this->mp; }
int character::getATK() const { return this->atk; }

// set stats
int character::setHP(int hp) {
    this->hp = (hp < 0) ? 0 : hp;
    return this->hp;
}
int character::setMP(int mp) {
    this->mp = (mp < 0) ? 0 : mp;

    if (!hasMP()) {
        this->mp = 0;
    }

    return this->mp;
}
int character::setATK(int atk) {
    this->atk = atk;
    return this->atk;
}

// basic operations
void character::heal(int hp) {
    setHP(getHP() + hp);
    std::cout << "HP:" << getHP() << std::endl;
}

void character::recover(int mp) {
    if (!hasHP()) {
        std::cout << "Character is dead." << std::endl;
        return;
    } else {
        setMP(getMP() + mp);
        std::cout << "MP:" << getMP() << std::endl;
    }
}

void character::hurt(int hp) {
    if (!hasHP()) {
        std::cout << "Character is dead." << std::endl;
        return;
    }

    setHP(getHP() - hp);

    if (!hasHP()) {
        std::cout << "Character is dead." << std::endl;
    } else {
        std::cout << "HP:" << getHP() << std::endl;
    }
}

// attacks
int character::cast(int mp) {
    if (!hasHP()) {
        std::cout << "Character is dead." << std::endl;
        return 0;
    }

    if (getMP() < mp) {
        std::cout << "Not enough MP." << std::endl;
        return 0;
    }

    setMP(getMP() - mp);
    std::cout << "MP:" << getMP() << std::endl;
    return getMP() * 0.5;
}
int character::attack() {
    if (!hasHP()) {
        std::cout << "Character is dead." << std::endl;
        return 0;
    }
    std::cout << "ATK:" << getATK() << std::endl;
    return getATK();
}