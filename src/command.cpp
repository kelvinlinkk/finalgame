#include "command.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "character.h"

// define commands
namespace GameSystem {
enum class Commands {
    set,
    info,
    heal,
    recover,
    hurt,
    cast,
    attack,
    exit,
    unknown
};

// set up mapping
static std::map<std::string, Commands> commandMap{
    {"set", Commands::set},       {"info", Commands::info},
    {"heal", Commands::heal},     {"recover", Commands::recover},
    {"hurt", Commands::hurt},     {"cast", Commands::cast},
    {"attack", Commands::attack}, {"exit", Commands::exit}};

// handling commands
bool handlingCommand(character& c, std::string input) {
    int temp;
    std::stringstream ss(input);
    std::string cmd;
    std::vector<int> args;

    ss >> cmd;
    while (ss >> temp) {
        args.push_back(temp);
    }
    Commands cmds = commandMap.count(cmd) ? commandMap[cmd] : Commands::unknown;
    try {
        switch (cmds) {
            case Commands::set:
                c.setINFO(args.at(0), args.at(1), args.at(2));
                break;
            case Commands::info:
                c.getINFO();
                break;
            case Commands::heal:
                c.heal(args.at(0));
                break;
            case Commands::recover:
                c.recover(args.at(0));
                break;
            case Commands::hurt:
                c.hurt(args.at(0));
                break;
            case Commands::cast:
                c.cast(args.at(0));
                break;
            case Commands::attack:
                c.attack();
                break;
            case Commands::exit:
                return false;
                break;
            case Commands::unknown:
                std::cout << "Invalid input." << std::endl;
                break;
            default:
                std::cout << "Invalid input." << std::endl;
                break;
        }
    } catch (const std::out_of_range& e) {
        std::cout << "Invalid input." << std::endl;
    }
    return true;
}
}  // namespace GameSystem