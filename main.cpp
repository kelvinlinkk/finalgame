#include "character.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string cmd = "";
    character c;
    
    while (cin >> cmd)
    {
        if (cmd == "set")
        {
            int hp, mp, atk;
            cin >> hp >> mp >> atk;
            c.setINFO(hp, mp, atk);
        }
        else if (cmd == "info")
        {
            c.getINFO();
        }
        else if (cmd == "heal")
        {
            int hp;
            cin >> hp;
            c.heal(hp);
        }
        else if (cmd == "recover")
        {
            int mp;
            cin >> mp;
            c.recover(mp);
        }
        else if (cmd == "hurt")
        {
            int hp;
            cin >> hp;
            c.hurt(hp);
        }
        else if (cmd == "cast")
        {
            int mp;
            cin >> mp;
            c.cast(mp);
        }
        else if (cmd == "attack")
        {
            c.attack();
        }
        else if (cmd == "exit")
        {
            break;
        }
        else
        {
            // Fixed: Handle invalid input
            cout << "Invalid input." << endl;
        }
    }
    return 0;
}