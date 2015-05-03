#ifndef SENSOR_HPP_
#define SENSOR_HPP_

struct SensorCoordinates {
    int x;
    int y;
};

typedef int SensorValue;

struct SensorData {
    SensorValue value;
    SensorCoordinates position;
};

#endif  // SENSOR_HPP_
