#include <hpc/sensors/Network.hpp>

SensorNetwork::SensorNetwork(int n)
    : _data(n) {}

const std::vector<SensorData>& SensorNetwork::data() const {
    return _data;
}

std::vector<SensorData>& SensorNetwork::data() {
    return _data;
}

#include <iostream>

void SensorNetwork::push() {
    // push data to DEVICE

    // test if kernel invocation works
    // works!
    network_push(_data);

    //test if C++11 works
    // works!
    for (auto x : std::vector<int>({11,22,33}))
        std::cout << x << std::endl;
}

void SensorNetwork::pull() {
    // pull data from DEVICE
    // kernel<<<1,1>>>();
}
