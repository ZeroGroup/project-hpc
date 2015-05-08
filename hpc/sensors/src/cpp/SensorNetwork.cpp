#include <hpc/sensors/SensorNetwork.hpp>

#include <hpc/sensors/Network.hpp>

SensorNetwork::SensorNetwork(int n) {}

SensorNetwork::~SensorNetwork(){}

void SensorNetwork::push() {
    // push data to DEVICE
    network_push();
}

void SensorNetwork::pull() {
    // pull messages from DEVICE
    network_pull();
}
