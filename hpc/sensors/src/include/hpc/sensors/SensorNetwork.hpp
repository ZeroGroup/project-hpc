#ifndef SENSOR_NETWORK_HPP_
#define SENSOR_NETWORK_HPP_

#include <iostream>
#include <vector>

#include <hpc/sensors/Sensor.hpp>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

class SensorNetwork {
    int _network_data; //!< introduced in version 1

public:
    SensorNetwork(int n = 4);
    virtual ~SensorNetwork();

    virtual void start();
    virtual void stop();

    virtual void push();
    virtual void pull();

    virtual void load(const std::string& filename);
    virtual void save(const std::string& filename);

private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        if (version >= 1){
            ar & boost::serialization::make_nvp("network_data", _network_data);
        }
    }
};

BOOST_CLASS_VERSION(SensorNetwork, 1)

#endif  // SENSOR_NETWORK_HPP_
