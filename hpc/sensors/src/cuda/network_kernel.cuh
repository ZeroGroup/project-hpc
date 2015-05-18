#ifndef NETWORK_KERNEL_CUH_
#define NETWORK_KERNEL_CUH_

#include <cstddef>

#include <cuda.h>
#include <curand_kernel.h>

template <typename T, std::size_t capacity = 32>
class CyclicBuffer {
    std::size_t _pos_read = 0;
    std::size_t _pos_write = 0;

    T _data[capacity];
public:
    typedef T value_type;

    __host__ __device__ void push(value_type value) {
        _data[_pos_write] = value;
        _pos_write = ((_pos_write + 1) % capacity);
    }

    __host__ __device__ value_type pop() {
        std::size_t loc_pos_read = _pos_read;
        _pos_read = ((_pos_read + 1) % capacity);

        return _data[loc_pos_read];
    }

    __host__ std::size_t size() const {
        return abs(_pos_write - _pos_read);
    }

    __host__ bool empty() const {
        return _pos_write == _pos_read;
    }
};

constexpr std::size_t CBUF_SIZE = 80;

__global__ void network_kernel(CyclicBuffer<int, CBUF_SIZE> * bufs, curandState * state);

#endif  // NETWORK_KERNEL_CUH_
