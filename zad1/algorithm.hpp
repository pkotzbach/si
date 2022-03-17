#pragma once
#include <array>
#include "dataProviders.hpp"
#include "factory.hpp"
#include "consts.hpp"

struct Algorithm
{
    std::array<Machine, consts::machinesAmmount> machines;
    std::vector<Factory> population;

    void feedMachines();
    int calculateCost(int factoryId);
    int getBestCost();
    void randPositions(int factoryId);
    void generatePositions(int factoryId);
    void printCosts();
    int tournamentSelection(int factoriesToPick);
    int rouletteSelection();
    Factory onePointCrossoverOperator(Factory &factory1, Factory &factory2);

    int getSafeCost(int factoryId);
};