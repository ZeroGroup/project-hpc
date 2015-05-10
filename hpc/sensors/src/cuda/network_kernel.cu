#include <hpc/sensors/Network.hpp>

#include "network_kernel.cuh"

__global__ void network_kernel(int *data) {
    __shared__ bool running;

    running = true;
    // __syncthreads()
    unsigned int x = blockIdx.x * blockDim.x + threadIdx.x;
    // unsigned int y = blockIdx.y * blockDim.y + threadIdx.y;

    __syncthreads();
    data[x] = static_cast<int>('A') + x;
    __syncthreads();

    // while (running) {
    //     __syncthreads();

    // }
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
