#include "algorithm.hpp"
#include "machine.hpp"
#include <stdlib.h>
#include <vector>
#include <algorithm>

inline int calculateDistance(const Position &pos1, const Position &pos2)
{
    // std::cout << pos1.x << " " << pos1.y << ", " << pos2.x << " " << pos2.y << std::endl;
    return abs(pos1.x - pos2.x) + abs(pos1.y - pos2.y);
}

void Algorithm::feedMachines()
{
    srand(time(NULL));
    MachinesBuilder machineBuilder;
    machineBuilder.readCost(consts::costPath);
    machineBuilder.readFlow(consts::flowPath);
    machines = machineBuilder.makeMachines();
}

long long Algorithm::calculateCost(int fabricId)
{
    long long cost = 0;
    for (int i = 0; i < machines.size(); ++i)
    {
        for (int j = i; j < machines.size(); ++j)
        {
            cost += machines[i].costs[j] * machines[i].flows[j] * calculateDistance(population[fabricId].machinesPositions[i], population[fabricId].machinesPositions[j]);
        }
    }
    return cost;
}

void Algorithm::randPositions(int fabricId)
{
    std::random_shuffle(positions.begin(), positions.end());
    for (int i = 0; i < consts::machinesAmmount; ++i)
    {
        population[fabricId].machinesPositions[i].x = positions[i].x;
        population[fabricId].machinesPositions[i].y = positions[i].y;
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
    for (int i = 0; i < population.size(); ++i)
    {
        std::cout << "population: " << i << ", cost: " << population[i].cost << std::endl;
    }
}