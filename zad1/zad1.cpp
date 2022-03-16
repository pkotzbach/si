#include <iostream>
#include <fstream>
#include "algorithm.hpp"
#include "consts.hpp"

#define mutationDebug 0

using json = nlohmann::json;

int main()
{
    Algorithm alg;

    alg.feedMachines();

    // init
    for (int i = 0; i < consts::populationSize; ++i)
    {
        alg.population.push_back({});
        alg.generatePositions(i);
        alg.randPositions(i);
    }

    long long cost = alg.getBestCost();
    std::cout << cost << std::endl;

    for (int i = 0; i < consts::howManyPopulations; ++i)
    {
        std::vector<Factory> newPopulation;
        while (newPopulation.size() < consts::populationSize)
        {
            // selection
            int parent1 = alg.tournamentSelection(consts::factoriesToPick);
            int parent2 = alg.tournamentSelection(consts::factoriesToPick);
            while (parent1 == parent2)
            {
                parent2 = alg.tournamentSelection(consts::factoriesToPick);
            }

            // crossover
            Factory newFactory = alg.onePointCrossoverOperator(alg.population[parent1], alg.population[parent2]);

            // mutation
            float mutationRandom = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            if (mutationRandom <= consts::mutationChance)
            {
                if (mutationDebug)
                {
                    std::cout << "wylosowalo liczbe " << mutationRandom << ", przeprowadzam mutacje\nfabryka przed mutacja" << std::endl;
                    newFactory.printPositions();
                }
                int changed = newFactory.mutate();
                if (mutationDebug)
                {
                    std::cout << "\nfabryka po mutacji, zmieniono " << changed << std::endl;
                    newFactory.printPositions();
                }
            }
            newPopulation.push_back(newFactory);
        }
        alg.population = newPopulation;
        std::cout << alg.getBestCost() << std::endl;
        if (alg.getBestCost() < cost)
            cost = alg.getBestCost();
    }

    // alg.printCosts();
    std::cout << cost;
}