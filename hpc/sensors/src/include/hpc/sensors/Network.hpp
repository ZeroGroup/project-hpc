#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <vector>

#include <hpc/sensors/Sensor.hpp>

class SensorNetwork {
    std::vector<SensorData> _data;
public:
    SensorNetwork(int n);

    const std::vector<SensorData>& data() const ;
    std::vector<SensorData>& data();

    void push();
    void pull();
};

// class NetworkObservator {
//     SensorNetwork _network;
// public:
//     NetworkObservator();
// };

void network_push(const std::vector<SensorData>& data);

#endif  // NETWORK_HPP_
