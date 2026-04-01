#include "gamesystem.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "character.h"

// define commands
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
bool handlingCommand(Party& p, std::string input) {
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
                // p.setINFO(args.at(0), std::stoi(args.at(1)), std::stoi(args.at(2)), std::stoi(args.at(3)));
                break;
            case Commands::info:
                p.getINFO();
                break;
            case Commands::heal:
                p.heal(args.at(0), std::stoi(args.at(1)));
                break;
            case Commands::recover:
                p.recover(args.at(0), std::stoi(args.at(1)));
                break;
            case Commands::hurt:
                p.hurt(args.at(0), std::stoi(args.at(1)));
                break;
            case Commands::cast:
                p.cast(args.at(0), std::stoi(args.at(1)));
                break;
            case Commands::attack:
                p.attack();
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