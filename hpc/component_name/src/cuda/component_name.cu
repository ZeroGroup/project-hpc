/**
    CUDA/C CODE
*/

#include <cstdlib>

#include <algorithm>

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/generate.h>
#include <thrust/reduce.h>
#include <thrust/functional.h>

int random_number(){
    return rand() % (1 << 16);
}

#include "hpc/component_name/Main.hpp"

int do_all(){
    // generate random data serially (1M)
    thrust::host_vector<int> h_vec(1 << 20);
    std::generate(h_vec.begin(), h_vec.end(), random_number);

    // transfer to device and compute sum
    thrust::device_vector<int> d_vec = h_vec;
    int x = thrust::reduce(d_vec.begin(), d_vec.end(), 0, thrust::plus<int>());

    return x;
}
