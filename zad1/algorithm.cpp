#include "algorithm.hpp"
#include "machine.hpp"
#include <stdlib.h>
#include <vector>
#include <algorithm>

#define lastPopulation populations.back().machinesPositions

void Algorithm::feedMachines()
{
    srand(time(NULL));
    MachinesBuilder machineBuilder;
    machineBuilder.readCost(consts::costPath);
    machineBuilder.readFlow(consts::flowPath);
    machines = machineBuilder.makeMachines();
}

void Algorithm::createNewPopulation()
{
    populations.push_back({});
}

inline int Algorithm::calculateDistance(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

long long Algorithm::calculateTotalCost()
{
    long long cost = 0;
    for (int i = 0; i < machines.size(); ++i)
    {
        for (int j = i; j < machines.size(); ++j)
        {
            cost += machines[i].costs[j] * machines[i].flows[j] * calculateDistance(lastPopulation[i].x, lastPopulation[i].y, lastPopulation[j].x, lastPopulation[j].y);
        }
    }
    return cost;
}

void Algorithm::randPositions()
{
    std::random_shuffle(positions.begin(), positions.end());
    for (int i = 0; i < consts::machinesAmmount; ++i)
    {
        lastPopulation[i] = positions[i];
    }
}

void Algorithm::generatePositions()
{
    for (int x = 0; x < consts::width; ++x)
    {
        for (int y = 0; y < consts::height; ++y)
        {
            positions[x * consts::height + y] = Position{x, y};
        }
    }
}

void Algorithm::printResults()
{
    for (int i = 0; i < populations.size(); ++i)
    {
        std::cout << "-------------------\npopulation: " << i << ", cost: " << populations[i].cost << std::endl;
        populations[i].printPositions();
    }
}