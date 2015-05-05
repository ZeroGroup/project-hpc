#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <vector>

#include <hpc/sensors/Sensor.hpp>

class SensorNetwork {
public:
    SensorNetwork(int n = 4);
    virtual ~SensorNetwork();

    virtual void push();
    virtual void pull();
};

void network_push();

#endif  // NETWORK_HPP_
