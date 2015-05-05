#include <hpc/sensors/Network.hpp>

#include <thrust/device_vector.h>

__global__ void kernel(int *data) {
    // __syncthreads()
   unsigned int x = blockIdx.x * blockDim.x + threadIdx.x;
   // unsigned int y = blockIdx.y * blockDim.y + threadIdx.y;

   data[x] = (static_cast<int>('A') + x);
}

/*
__global__ void sensor_kernel() {
    value_type value;
    while (true) {
        get_messages();
        __synchronize();
        read_physical_data();
        __synchronize();
        send_messages();
    }
}*/

#include <iostream>

void network_push(){

    thrust::device_vector<int> dev_v(16);
    // for (int i = 0; i < 16; ++i){
    //     int* raw_ptr;

    //     dev_v.push_back(raw_ptr);
    // }

    kernel<<<1,16>>>(thrust::raw_pointer_cast(dev_v.data()));

    for (int a : dev_v)
        std::cout << static_cast<char>(a) << std::endl;
}
