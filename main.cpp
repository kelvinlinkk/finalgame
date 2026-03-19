#include <iostream>
#include <string>

#include "character.h"
#include "command.h"

using namespace std;

int main() {
    string cmd = "";
    character *c=new character();

    do {
        getline(cin, cmd);
    } while (GameSystem::handlingCommand(*c, cmd));
    delete c;
    return 0;
}