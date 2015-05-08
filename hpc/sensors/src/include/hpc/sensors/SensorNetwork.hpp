#ifndef SENSOR_NETWORK_HPP_
#define SENSOR_NETWORK_HPP_

#include <vector>

#include <hpc/sensors/Sensor.hpp>

class SensorNetwork {
public:
    SensorNetwork(int n = 4);
    virtual ~SensorNetwork();

    virtual void start();
    virtual void stop();

    virtual void push();
    virtual void pull();
};

#endif  // SENSOR_NETWORK_HPP_
