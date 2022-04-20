#include "include/dataMemory.h"

#include <math.h>

#include <iostream>

namespace riscv_emulator {

void DataMemory::set_cache_val(int address, bool val[CACHE_BITS_PER_ADDRESS]) {
    for (int i = 0; i < CACHE_BITS_PER_ADDRESS; i++) {
        this->Cache[address][i] = val[i];
    }
}

unsigned long DataMemory::get_cache_val(int address) {
    unsigned long val = 0;
    for (int i = 0; i < CACHE_BITS_PER_ADDRESS; i++) {
        val += this->Cache[address][i]*std::pow(2,i);
    }
    return val;
}

void DataMemory::copy_cache_val(int address, bool given_array[CACHE_BITS_PER_ADDRESS]) {
    for (int i = 0; i < CACHE_BITS_PER_ADDRESS; i++) {
        given_array[i] = this->Cache[address][i];
    }
}

DataMemory::DataMemory() {
    // zero out memory for default constructor
    for (int i = 0; i < CACHE_NUM_ADDRESSES; i++) {
        for (int j = 0; j < CACHE_BITS_PER_ADDRESS; j++) {
            this->Cache[i][j] = 0;
        }
    }
}

} // namespace riscv_emulator