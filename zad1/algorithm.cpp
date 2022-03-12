#include "algorithm.hpp"
#include "machine.hpp"
#include <stdlib.h>
#include <vector>

void Algorithm::feedMachines()
{
    srand(time(NULL));
    MachinesBuilder machineBuilder;
    machineBuilder.readCost(consts::costPath);
    machineBuilder.readFlow(consts::flowPath);
    machines = machineBuilder.makeMachines();
    results.push_back({});
}

inline int Algorithm::calculateDistance(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

int Algorithm::calculateTotalCost()
{
    int cost = 0;
    for (int i = 0; i < machines.size(); ++i)
    {
        for (int j = i; j < machines.size(); ++j)
        {
            cost += machines[i].costs[j] * machines[i].flows[j] * calculateDistance(machines[i].x, machines[i].y, machines[j].x, machines[j].y);
        }
    }
    return cost;
}

void Algorithm::randPositions()
{
    int x, y;
    std::vector<Result> usedCords;
    for (auto &result : results.back())
    {
        x = rand() % consts::width;
        y = rand() % consts::height;
        while (std::count(usedCords.begin(), usedCords.end(), std::pair<int, int>(x, y)))
        {
            x = rand() % consts::width;
            y = rand() % consts::height;
        }
        machine.x = x;
        machine.y = y;
        usedCords.push_back(std::pair<int, int>(x, y));
    }
}