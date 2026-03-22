#pragma once
#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include <map>
#include "character.h"

namespace GameSystem {
    enum class Commands;
    bool handlingCommand(character&, std::string);
}  // namespace GameSystem
#endif