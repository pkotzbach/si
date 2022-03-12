#include "machine.hpp"
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

    for (const auto &elem : flow)
    {
        machines[elem["source"]].flows[elem["dest"]] = elem["amount"];
        // machines[elem["dest"]].flows[elem["source"]] = elem["amount"];
        machines[elem["dest"]].flows[elem["source"]] = -1;
    }

    for (const auto &elem : cost)
    {
        machines[elem["source"]].costs[elem["dest"]] = elem["cost"];
        // machines[elem["dest"]].costs[elem["source"]] = elem["cost"];
        machines[elem["dest"]].costs[elem["source"]] = -1;
    }

    for (int i = 0; i < consts::machinesAmmount; ++i)
    {
        machines[i].flows[i] = -1;
        machines[i].costs[i] = -1;
    }

    return std::move(machines);
}