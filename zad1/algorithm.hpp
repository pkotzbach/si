#pragma once
#include <array>
#include "machine.hpp"
#include "consts.hpp"

struct Fabric
{
    std::array<Position, consts::machinesAmmount> machinesPositions;
    long long cost;
    void printPositions()
    {
        for (int i = 0; i < machinesPositions.size(); ++i)
        {
            std::cout << "machine " << i << ": " << machinesPositions[i].toString() << std::endl;
        }
    }
};

struct Algorithm
{
    std::array<Machine, consts::machinesAmmount> machines;
    std::array<Fabric, consts::populationSize> population;
    std::array<Position, consts::width * consts::height> positions;

    void feedMachines();
    long long calculateCost(int fabricId);
    void randPositions(int fabricId);
    void generatePositions();
    void printResults();
};