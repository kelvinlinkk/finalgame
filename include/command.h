#pragma once
#ifndef COMMAND_H
#define COMMAND_H
#include <string>

#include "character.h"
enum class Commands;
bool handlingCommand(character&, std::string);
#endif