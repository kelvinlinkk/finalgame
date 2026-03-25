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
bool handlingCommand(Character& c, std::string input) {
    std::string temp;
    std::stringstream ss(input);
    std::string cmd;
    std::vector<std::string> args;

    ss >> cmd;
    while (ss >> temp) {
        args.push_back(temp);
    }
    Commands cmds = commandMap.count(cmd) ? commandMap[cmd] : Commands::unknown;
    try {
        switch (cmds) {
            case Commands::set:
                c.setINFO(args.at(0), std::stoi(args.at(1)), std::stoi(args.at(2)),std::stoi(args.at(3)));
                break;
            case Commands::info:
                c.getINFO();
                break;
            case Commands::heal:
                c.heal(std::stoi(args.at(0)));
                break;
            case Commands::recover:
                c.recover(std::stoi(args.at(0)));
                break;
            case Commands::hurt:
                c.hurt(std::stoi(args.at(0)));
                break;
            case Commands::cast:
                c.cast(std::stoi(args.at(0)));
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