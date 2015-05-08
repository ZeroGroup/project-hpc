#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_

#include <hpc/sensors/Sensor.hpp>

typedef int Timestamp;

class Message {
    Timestamp time;
    SensorData data;
};

#endif  // MESSAGE_HPP_
