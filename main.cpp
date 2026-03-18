#include <iostream>
#include <string>

#include "character.h"
#include "command.h"

using namespace std;

int main() {
    string cmd = "";
    character c;

    do {
        getline(cin, cmd);
    } while (handlingCommand(c, cmd));
    return 0;
}