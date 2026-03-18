#pragma once
#ifndef CHARACTER
#define CHARACTER
class character
{
private:
    int hp;
    int mp;
    int atk;

public:
    character();
    character(int, int, int);
    ~character();
    // character status
    void getINFO() const;
    void setINFO(int, int, int);
    bool hasHP() const;
    bool hasMP() const;

    // get stats
    int getHP() const;
    int getMP() const;
    int getATK() const;

    // set stats
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