#include "factory.hpp"

void Factory::printPositions() const
{
    for (int i = 0; i < positions.size(); ++i)
    {
        std::cout << positions[i].toString() << ", machine: " << positions[i].machineId << std::endl;
    }
}

Position Factory::getPositionForMachine(int machineId) const
{
    for (int i = 0; i < positions.size(); ++i)
    {
        if (positions[i].machineId == machineId)
        {
            return positions[i];
        }
    }
    return Position{-1, -1, -1};
}

int Factory::mutate()
{
    int pos1 = std::rand() % positions.size();
    int pos2 = std::rand() % positions.size();
    while (pos1 == pos2)
    {
        pos2 = std::rand() % positions.size();
    }
    std::swap(positions[pos1].machineId, positions[pos2].machineId);
    return pos1;
}