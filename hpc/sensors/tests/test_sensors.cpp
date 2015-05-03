#include <iostream>

#include <hpc/sensors/Sensor.hpp>
#include <hpc/sensors/Network.hpp>

using namespace std;

int main(int ac, char *av[]){
    cout << "Hello, World!" << endl;

    SensorNetwork net(5);
    net.push();

    return 0;
}
