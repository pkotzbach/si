#include "dataProviders.hpp"
#include <fstream>
#include "consts.hpp"
#include <iostream>

bool MachinesBuilder::readFlow(const std::string &path)
{
    std::ifstream stream;
    stream.open(path);
    if (!stream)
    {
        return false;
    }
    stream >> flow;
    return true;
}

bool MachinesBuilder::readCost(const std::string &path)
{
    std::ifstream stream;
    stream.open(path);
    if (!stream)
    {
        return false;
    }
    stream >> cost;
    return true;
}

std::array<Machine, consts::machinesAmmount> MachinesBuilder::makeMachines()
{
    std::array<Machine, consts::machinesAmmount> machines;

    for (int i = 0; i < consts::machinesAmmount; ++i)
    {
        for (int j = 0; j < consts::machinesAmmount; ++j)
        {
            machines[i].flows[j] = 0;
            machines[i].costs[j] = 0;
        }
    }

    for (const auto &elem : flow)
    {
        machines[elem["source"]].flows[elem["dest"]] = elem["amount"];
        machines[elem["dest"]].flows[elem["source"]] = elem["amount"];
    }

    for (const auto &elem : cost)
    {
        machines[elem["source"]].costs[elem["dest"]] = elem["cost"];
        machines[elem["dest"]].costs[elem["source"]] = elem["cost"];
    }

    // for (int i = 0; i < consts::machinesAmmount; ++i)
    // {
    //     for (int j = i; j < consts::machinesAmmount; ++j)
    //     {
    //         std::cout << "i: " << i << ", j: " << j << " - " << machines[i].costs[j] << " " << machines[i].flows[j] << std::endl;
    //     }
    // }

    return machines;
}