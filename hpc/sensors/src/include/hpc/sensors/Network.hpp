#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <queue>

#include <thrust/device_vector.h>

#include <hpc/sensors/Message.hpp>
#include <hpc/sensors/World.hpp>

extern thrust::device_vector<int> _device_values;
extern thrust::device_vector<SensorCoordinates> _device_coordinates;

void network_init();
void network_destroy();

void network_start();
void network_stop();

void network_push(WorldUpdateDataStream& data);
std::queue<Message> network_pull();

#endif  // NETWORK_HPP_
