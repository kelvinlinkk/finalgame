#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "character.h"
#include "gamemanager.h"
#include "weapon.h"

// command list;
enum class Commands { set, info, heal, recover, hurt, cast, attack, unknown };

// mapping strings to commands
static std::map<std::string, Commands> commandMap{
    {"set", Commands::set},      {"info", Commands::info},
    {"heal", Commands::heal},    {"recover", Commands::recover},
    {"hurt", Commands::hurt},    {"cast", Commands::cast},
    {"attack", Commands::attack}};

gameManager::gameManager(std::string partyname, std::string warriorname,
                         std::string fightername, std::string magename)
    : playerparty(partyname, warriorname, fightername, magename),
      isGameover(true) {
    this->enemy =
        std::make_unique<Character>("Slime", 120, 10, 40, "sticky ball");
}

// game flow
void gameManager::startGame() {
    int round = 1;
    isGameover = false;
    {
        std::string _;
        getline(std::cin, _);
    }
    std::cout << "Fight start!" << std::endl << std::endl;
    while (!isGameover) {
        std::cout << "Round " << round << std::endl;
        enemy->getINFO();
        playerparty.getINFO();
        playerTurn();
        if (!enemy->hasHP()) {
            std::cout << "You beat the Enemy:" << enemy->getName() <<"!"<<std::endl;
            isGameover = true;
            return;
        }
        playerparty.partyHurt("all", enemy->attack());

        if (!playerparty.isAlive) {
            std::cout << "You have been defeated!" <<std::endl;
            isGameover = true;
            return;
        }
        round++;
        std::cout<<std::endl;
    }
    return;
}

void gameManager::playerTurn() {
    std::string cmd = "";
    std::cout << "Input your action:" << std::endl;
    while (getline(std::cin, cmd)) {
        if (handlingCommand(cmd)) {
            return;
        }
    }
}

bool gameManager::handlingCommand(std::string input) {
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
                // playerparty.setINFO(args.at(0), std::stoi(args.at(1)),
                // std::stoi(args.at(2)), std::stoi(args.at(3)));
                break;
            case Commands::info:
                playerparty.getINFO();
                break;
            case Commands::heal:
                playerparty.partyHeal(args.at(0), std::stoi(args.at(1)));
                break;
            case Commands::recover:
                playerparty.partyRecover(args.at(0), std::stoi(args.at(1)));
                break;
            case Commands::hurt:
                playerparty.partyHurt(args.at(0), std::stoi(args.at(1)));
                break;
            case Commands::cast:
                    playerparty.partyCast(args.at(0), std::stoi(args.at(1)));
                break;
            case Commands::attack:
                enemy->hurt(playerparty.partyAttack());
                break;
            case Commands::unknown:
                std::cout << "Invalid input." << std::endl;
                break;
            default:
                std::cout << "Invalid input." << std::endl;
        }
    } catch (const std::out_of_range& e) {
        std::cout << "Invalid input." << std::endl;
    }
    return true;
}
