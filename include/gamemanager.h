#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <map>
#include <memory>
#include <string>

#include "character.h"
#include "party.h"

class gameManager {
   private:
    Party playerparty;
    std::shared_ptr<Character> enemy;
    bool handlingCommand(std::string );
    bool isGameover;
    void playerTurn();

   public:
    gameManager(std::string, std::string, std::string, std::string);
    void startGame();
};
#endif
