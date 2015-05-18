#include <hpc/sensors/Network.hpp>

#include <unistd.h>

#include "network_kernel.cuh"

#include <cuda.h>
#include <curand_kernel.h>

#include <cstdlib>
#include <ctime>

#include <iostream>
#include <iomanip>

__global__ void curand_setup_kernel(curandState * state, unsigned long seed = 0) {
    int id = threadIdx.x + blockIdx.x * blockDim.x;

    /* Each thread gets same seed, a different sequence
       number, no offset */
    curand_init(seed, id, 0, &state[id]);
}

void network_start() {
    constexpr unsigned BLK_COUNT = 1;
    constexpr unsigned THREADS_PER_BLK = 16;

    thrust::device_vector<CyclicBuffer<int, CBUF_SIZE>> dev_v(BLK_COUNT * THREADS_PER_BLK);

    curandState * devStates;
    cudaMalloc((void **)&devStates, BLK_COUNT * THREADS_PER_BLK * sizeof(curandState));

    srand(time(NULL));

    curand_setup_kernel<<<BLK_COUNT, THREADS_PER_BLK>>>(devStates, rand());
    network_kernel<<<BLK_COUNT, THREADS_PER_BLK>>>(thrust::raw_pointer_cast(dev_v.data()), devStates);

    thrust::host_vector<CyclicBuffer<int, CBUF_SIZE>> host_v = dev_v;

    std::cout << "wait 0.1 sec" << std::endl;
    usleep(100000);

    host_v = dev_v;

    for (auto & a : host_v) {
        std::cout << std::setw(3) << a.size() << ": ";

        while(!a.empty())
            std::cout << static_cast<char>(a.pop());

        std::cout << std::endl;
    }

    cudaFree(devStates);
}
