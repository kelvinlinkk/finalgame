#pragma once
#ifndef COMMAND_H
#define COMMAND_H
#include <map>
#include <string>

#include "party.h"

enum class Commands;
bool handlingCommand(Party&, std::string);
#endif