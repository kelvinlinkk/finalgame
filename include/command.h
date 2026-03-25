#pragma once
#ifndef COMMAND_H
#define COMMAND_H
#include <map>
#include <string>

#include "character.h"

namespace GameSystem {
enum class Commands;
bool handlingCommand(Character&, std::string);
}  // namespace GameSystem
#endif