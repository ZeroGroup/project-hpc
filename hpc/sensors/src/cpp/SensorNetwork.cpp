#include <hpc/sensors/SensorNetwork.hpp>

#include <hpc/sensors/Network.hpp>
#include <hpc/sensors/World.hpp>

SensorNetwork::SensorNetwork(int n) {
    network_init();
}

SensorNetwork::~SensorNetwork() {
    network_destroy();
}

void SensorNetwork::start() {
    network_start();
}

void SensorNetwork::stop() {
    network_stop();
}

void SensorNetwork::push() {
    // create WorldInfoDataStream
    WorldUpdateDataStream datastream;
    // fill update info
    // ...
    // push data to DEVICE
    network_push(datastream);
}

void SensorNetwork::pull() {
    // pull messages from DEVICE
    std::queue<Message> messages = network_pull();

    // process messages
    // ...
}
