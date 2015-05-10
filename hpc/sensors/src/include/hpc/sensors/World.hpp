#ifndef WORLD_HPP_
#define WORLD_HPP_

#include <queue>
#include <vector>

#include <hpc/sensors/Sensor.hpp>

//! POD
struct WorldInfoEntry {

};

typedef std::queue<WorldInfoEntry> WorldUpdateDataStream;
typedef std::vector<WorldInfoEntry> WorldInfo;

#endif  // WORLD_HPP_
