#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include<memory>
#include "weapon.h"
class Character {
   private:
    int hp;
    int mp;
    int atk;
    std::string name;
    std::unique_ptr<Weapon> weapon;

   public:
    Character();
    Character(std::string, int, int, int, Weapon&);
    ~Character();
    // character status
    void INFO() const;
    void getINFO() const;
    void setINFO(std::string, int, int, int);
    bool hasHP() const;
    bool hasMP() const;

    // get stats
    std::string getName() const;
    int getHP() const;
    int getMP() const;
    int getATK() const;

    // set stats
    std::string setName(std::string);
    int setHP(int);
    int setMP(int);
    int setATK(int);

    // basic operations
    void heal(int);
    void recover(int);
    void hurt(int);

    // attacks
    int cast(int);
    int attack();
};
#endif
