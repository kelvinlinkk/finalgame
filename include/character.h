#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include<memory>
#include "weapon.h"
class Character {
   protected:
    int hp;
    int mp;
    int atk;
    std::string name;
    std::unique_ptr<Weapon> weapon;

   public:
    Character();
    Character(std::string, int, int, int, std::string);
    /*virtual*/ ~Character();
    // character status
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
    virtual void action(std::shared_ptr<Character>)=0;

    void heal(int);
    void recover(int);
    void hurt(int);
    int cast();
    int attack();

    // operator overload
    friend std::ostream& operator<<(std::ostream&, const Character&);
    Character& operator++();
    Character& operator+=(std::unique_ptr<Weapon>);
};

class Hero:public Character {
   public:
    Hero();
    Hero(std::string, int, int, int, std::string);
    void action(std::shared_ptr<Character> target) override;
    ~Hero();
    int cast();
};


class Warrior:public Character {
   public:
    Warrior();
    Warrior(std::string, int, int, int, std::string);
    void action(std::shared_ptr<Character> target) override;
    ~Warrior();
    int cast() ;
};
class Mage:public Character {
   public:
    Mage();
    Mage(std::string, int, int, int, std::string);
    void action(std::shared_ptr<Character> target) override;
    ~Mage();
    int cast() ;
};
class Monster:public Character {
   public:
    Monster();
    Monster(std::string, int, int, int, std::string);
    void action(std::shared_ptr<Character> target) override{};
    ~Monster();
};
#endif