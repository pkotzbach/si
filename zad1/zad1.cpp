#include <iostream>
#include <fstream>
#include "algorithm.hpp"
#include "consts.hpp"

using json = nlohmann::json;

int main()
{
    Algorithm alg;
    long long cost = 94832908519, newCost;

    alg.feedMachines();
    alg.generatePositions();
    for (int j = 0; j < 1; ++j)
    {
        cost = 94832908519;
        alg.createNewPopulation();
        for (int i = 0; i < 10000; ++i)
        {
            alg.randPositions();
            newCost = alg.calculateTotalCost();
            if (newCost < cost)
            {
                cost = newCost;
            }
        }
        alg.populations.back().cost = cost;
    }
    // std::cout << alg.results.size();
    alg.printResults();
}