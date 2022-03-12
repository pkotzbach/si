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

    void print()
    {
        std::cout << "x: " << x << ", y: " << y << std::endl;
        for (int i = 0; i < consts::machinesAmmount; i++)
        {
            std::cout << "machine: " << i << ", cost: " << costs[i] << ", flow: " << flows[i] << std::endl;
        }
    }
};

struct Result
{
    int x;
    int y;
};

struct MachinesBuilder
{
    json flow;
    json cost;

    bool readFlow(const std::string &path);
    bool readCost(const std::string &path);

    std::array<Machine, consts::machinesAmmount> makeMachines();
};