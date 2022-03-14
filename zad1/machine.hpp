#pragma once

#include <nlohmann/json.hpp>
#include <map>
#include <iostream>
#include "consts.hpp"
#include <array>

using json = nlohmann::json;

struct Machine
{
    int costs[consts::machinesAmmount];
    int flows[consts::machinesAmmount];
};

struct Position
{
    int x;
    int y;

    // void print() { std::cout << x << " " << y << std::endl; }
    std::string toString() { return "(" + std::to_string(x) + ", " + std::to_string(y) + ")"; }
};

struct MachinesBuilder
{
    json flow;
    json cost;

    bool readFlow(const std::string &path);
    bool readCost(const std::string &path);

    std::array<Machine, consts::machinesAmmount> makeMachines();
};