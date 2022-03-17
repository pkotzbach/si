#pragma once
#include "dataProviders.hpp"

struct Factory
{
    std::array<Position, consts::width * consts::height> positions;
    int cost = -1;

    void printPositions() const;
    Position getPositionForMachine(int machineId) const;
    int mutate();
};