#pragma once
#ifndef COMMAND_H
#define COMMAND_H
#include <map>
#include <string>
#include<memory>

#include"character.h"
#include "party.h"

enum class Commands;
bool handlingCommand(Party&, std::string);
class gameManager{
private:
  party playerparty;
  std::shared_ptr<Character> enemy;
  bool isGameover;
  void playerTurn();
public:
  gameManager(std::string, std::string,std::string,std::string);
  void startgame();
}
#endif
