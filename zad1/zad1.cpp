#include <iostream>
#include <fstream>
#include "algorithm.hpp"
#include "consts.hpp"

using json = nlohmann::json;

int main()
{
    Algorithm alg;
    alg.feedMachines();
    // alg.machines[0].print();
    int cost = 1000000, newCost;
    for (int i = 0; i < 20000; ++i)
    {
        alg.randPositions();
        newCost = alg.calculateTotalCost();
        // std::cout << newCost << std::endl;
        if (newCost < cost)
        {
            cost = newCost;
        }
    }
    std::cout << cost;
}