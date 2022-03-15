#include <iostream>
#include <fstream>
#include "algorithm.hpp"
#include "consts.hpp"

using json = nlohmann::json;

int main()
{
    Algorithm alg;

    alg.feedMachines();
    alg.generatePositions();
    int cost = 100000;
    for (int i = 0; i < consts::populationSize; ++i)
    {
        alg.randPositions(i);
        alg.population[i].cost = alg.calculateCost(i);
        if (alg.population[i].cost < cost)
            cost = alg.population[i].cost;
    }

    // alg.printResults();
    std::cout << cost;
}