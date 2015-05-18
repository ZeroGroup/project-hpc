#include <hpc/sensors/Network.hpp>

#include <cuda.h>
#include <sys/time.h>

#include "network_kernel.cuh"

#include <cuda.h>
#include <curand.h>
#include <curand_kernel.h>

__device__ void wait10kclocks() {
    clock_t start_clock = clock();

    while (clock() - start_clock < 10000);
}

__global__ void network_kernel(CyclicBuffer<int, 80> * bufs, curandState * state){
    unsigned int id = blockIdx.x * blockDim.x + threadIdx.x;

    curandState localState = state[id];

    int c = 0;
    bool random_bit = false;

    __syncthreads();
    while (++c < 20){
        random_bit = static_cast<bool>(curand(&localState) & 1);

        if (random_bit){
            bufs[id].push(static_cast<int>('A') + (c % ('Z' - 'A')));
        }

        __syncthreads();
    }

    state[id] = localState;
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
