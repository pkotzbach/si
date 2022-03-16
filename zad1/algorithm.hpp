#pragma once
#include <array>
#include "machine.hpp"
#include "consts.hpp"

struct Factory
{
    std::array<Position, consts::width * consts::height> positions;
    long long cost = -1;

    void printPositions()
    {
        for (int i = 0; i < positions.size(); ++i)
        {
            std::cout << positions[i].toString() << ", machine: " << positions[i].machineId << std::endl;
        }
    }

    Position getPositionForMachine(int machineId)
    {
        for (int i = 0; i < positions.size(); ++i)
        {
            if (positions[i].machineId == machineId)
            {
                return positions[i];
            }
        }
        return Position{-1, -1, -1};
    }

    int mutate()
    {
        int pos1 = std::rand() % positions.size();
        int pos2 = std::rand() % positions.size();
        while (pos1 == pos2)
        {
            pos2 = std::rand() % positions.size();
        }
        std::swap(positions[pos1].machineId, positions[pos2].machineId);
        return pos1;
    }
};

struct Algorithm
{
    std::array<Machine, consts::machinesAmmount> machines;
    std::vector<Factory> population;

    void feedMachines();
    long long calculateCost(int factoryId);
    long long getBestCost();
    void randPositions(int factoryId);
    void generatePositions(int factoryId);
    void printCosts();
    int tournamentSelection(int factoriesToPick);
    void repairFactory(Factory &factory);
    Factory onePointCrossoverOperator(Factory &factory1, Factory &factory2);

    long long getSafeCost(int factoryId);
};