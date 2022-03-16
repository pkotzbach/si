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
    int machineId;

    std::string toString() { return "(" + std::to_string(x) + ", " + std::to_string(y) + ")"; }
    bool operator==(Position &pos)
    {
        return pos.x == x && pos.y == y;
    }
};

struct MachinesBuilder
{
    json flow;
    json cost;

    bool readFlow(const std::string &path);
    bool readCost(const std::string &path);

    std::array<Machine, consts::machinesAmmount> makeMachines();
};