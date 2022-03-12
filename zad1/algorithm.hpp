#pragma once
#include <array>
#include "machine.hpp"
#include "consts.hpp"

struct Algorithm
{
    std::array<Machine, consts::machinesAmmount> machines;
    std::vector<std::array<Result, consts::machinesAmmount>> results;

    void feedMachines();
    int calculateTotalCost();
    inline int calculateDistance(int x1, int y1, int x2, int y2);
    void randPositions();
};