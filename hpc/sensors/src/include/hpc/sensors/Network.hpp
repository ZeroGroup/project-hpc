#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <queue>

#include <hpc/sensors/Message.hpp>
#include <hpc/sensors/World.hpp>

void network_push(WorldUpdateDataStream& data);
std::queue<Message> network_pull();

#endif  // NETWORK_HPP_
