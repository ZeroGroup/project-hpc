#include <hpc/sensors/Network.hpp>

__global__ void kernel(){

}

void network_push(const std::vector<SensorData>& data) {
    kernel<<<1,1>>>();
}

