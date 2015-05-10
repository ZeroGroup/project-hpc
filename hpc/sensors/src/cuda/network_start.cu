#include <hpc/sensors/Network.hpp>

#include "network_kernel.cuh"

void network_start(){
    thrust::device_vector<int> dev_v(16);
    // for (int i = 0; i < 16; ++i){
    //     int* raw_ptr;

    //     dev_v.push_back(raw_ptr);
    // }

    network_kernel<<<1,16>>>(thrust::raw_pointer_cast(dev_v.data()));

    for (int a : dev_v)
        std::cout << static_cast<char>(a) << std::endl;
}
