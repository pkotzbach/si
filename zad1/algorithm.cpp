#include "algorithm.hpp"
#include "machine.hpp"
#include <stdlib.h>
#include <vector>
#include <algorithm>

#define tournamentSelectionDebug 0
#define onePointCrossoverOperatorDebug 0

inline int calculateDistance(const Position &pos1, const Position &pos2)
{
    return abs(pos1.x - pos2.x) + abs(pos1.y - pos2.y);
}

int positionInVector(int value, const std::vector<int> &vector)
{
    for (int i = 0; i < vector.size(); ++i)
    {
        if (vector[i] == value)
            return i;
    }
    return -1;
}

void Algorithm::feedMachines()
{
    srand(time(NULL));
    MachinesBuilder machineBuilder;
    machineBuilder.readCost(consts::costPath);
    machineBuilder.readFlow(consts::flowPath);
    machines = machineBuilder.makeMachines();
}

long long Algorithm::calculateCost(int factoryId)
{
    long long cost = 0;
    for (int i = 0; i < population[factoryId].positions.size(); ++i)
    {
        if (population[factoryId].positions[i].machineId != -1)
        {
            int m1 = population[factoryId].positions[i].machineId;

            for (int j = i; j < population[factoryId].positions.size(); ++j)
            {
                if (population[factoryId].positions[j].machineId != -1)
                {
                    int m2 = population[factoryId].positions[j].machineId;
                    int temp = machines[m1].costs[m2] * machines[m1].flows[m2] * calculateDistance(population[factoryId].positions[i], population[factoryId].positions[j]);
                    // std::cout << m1 << " " << m2 << ", " << machines[m1].costs[m2] << " " << machines[m1].flows[m2] << " " << calculateDistance(population[factoryId].positions[i], population[factoryId].positions[j]) << std::endl;
                    cost += machines[m1].costs[m2] * machines[m1].flows[m2] * calculateDistance(population[factoryId].positions[i], population[factoryId].positions[j]);
                }
            }
        }
    }
    return cost;
}

void Algorithm::randPositions(int factoryId)
{
    for (auto &pos : population[factoryId].positions)
    {
        pos.machineId = -1;
    }
    for (int i = 0; i < consts::machinesAmmount; ++i)
    {
        int positionNum = -1;
        do
        {
            positionNum = std::rand() % population[factoryId].positions.size();
        } while (population[factoryId].positions[positionNum].machineId != -1);
        population[factoryId].positions[positionNum].machineId = i;
    }
}

void Algorithm::generatePositions(int factoryId)
{
    for (int x = 0; x < consts::width; ++x)
    {
        for (int y = 0; y < consts::height; ++y)
        {
            population[factoryId].positions[x * consts::height + y] = Position{x, y, -1};
        }
    }
}

void Algorithm::printCosts()
{
    for (int i = 0; i < population.size(); ++i)
    {
        std::cout << "-------------\n";
        std::cout << "population: " << i << ", cost: " << population[i].cost << std::endl;
        population[i].printPositions();
    }
}

long long Algorithm::getBestCost()
{
    long long min = getSafeCost(0);
    for (int i = 1; i < population.size(); ++i)
    {
        long long temp = getSafeCost(i);
        if (temp < min)
            min = temp;
    }
    return min;
}

int Algorithm::tournamentSelection(int factoriesToPick)
{
    assert(factoriesToPick > 0 && factoriesToPick <= consts::populationSize);
    std::vector<int> picked;
    int randomNum;
    for (int i = 0; i < factoriesToPick; ++i)
    {
        do
        {
            randomNum = rand() % consts::populationSize;
        } while (std::count(picked.begin(), picked.end(), randomNum));
        picked.push_back(randomNum);
    }
    if (tournamentSelectionDebug)
    {
        std::cout << "wybrano fabryki:\n";
        for (int i = 0; i < picked.size(); ++i)
        {
            std::cout << picked[i] << ", koszt: " << getSafeCost(picked[i]) << std::endl;
        }
    }

    int winnerId = picked[0];

    for (int i = 1; i < picked.size(); ++i)
    {
        if (getSafeCost(picked[i]) < getSafeCost(winnerId))
        {
            winnerId = picked[i];
        }
    }

    if (tournamentSelectionDebug)
    {
        std::cout << "zwyciezca: " << winnerId << std::endl;
    }

    return winnerId;
}

// int Algorithm::rouletteSelection()
// {

// }

Factory Algorithm::onePointCrossoverOperator(Factory &factory1, Factory &factory2)
{
    int crossoverPoint = (std::rand() % (consts::width * consts::height)) + 1;
    Factory factory;
    factory.positions = factory1.positions;
    std::vector<int> deleted;
    std::vector<int> added;

    for (int i = 0; i < crossoverPoint; ++i)
    {
        int posD = positionInVector(factory2.positions[i].machineId, deleted);
        if (posD == -1)
        {
            added.push_back(factory2.positions[i].machineId);
        }
        else
        {
            deleted.erase(deleted.begin() + posD);
        }

        int posA = positionInVector(factory.positions[i].machineId, added);
        if (posA == -1)
        {
            deleted.push_back(factory.positions[i].machineId);
        }
        else
        {
            added.erase(added.begin() + posA);
        }

        factory.positions[i] = factory2.positions[i];
    }

    assert(deleted.size() == added.size());

    // shuffle deleted added

    for (int i = crossoverPoint; i < (consts::width * consts::height); ++i)
    {
        int pos = positionInVector(factory.positions[i].machineId, added);
        if (pos != -1)
        {
            added.erase(added.begin() + pos);
            factory.positions[i].machineId = deleted.back();
            deleted.pop_back();
        }
    }

    if (onePointCrossoverOperatorDebug)
    {
        std::cout << "\ncrossoverPoint: " << crossoverPoint << std::endl;
        std::cout << "        factory1 factory2 factory\n";
        for (int i = 0; i < factory.positions.size(); ++i)
        {
            std::cout << factory1.positions[i].toString() << ": " << factory1.positions[i].machineId
                      << "          " << factory2.positions[i].machineId
                      << "          " << factory.positions[i].machineId << std::endl;
        }
    }
    return factory;
}

long long Algorithm::getSafeCost(int factoryId)
{
    if (population[factoryId].cost == -1)
    {
        population[factoryId].cost = calculateCost(factoryId);
    }
    return population[factoryId].cost;
}