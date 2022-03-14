#pragma once
#include <array>
#include "machine.hpp"
#include "consts.hpp"

struct Population
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
    std::vector<Population> populations;
    std::array<Position, consts::width * consts::height> positions;

    void feedMachines();
    long long calculateTotalCost();
    inline int calculateDistance(int x1, int y1, int x2, int y2);
    void randPositions();
    void generatePositions();
    void createNewPopulation();
    void printResults();
};