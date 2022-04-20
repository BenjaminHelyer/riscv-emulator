#include "include/register.h"

#include <math.h>

#include <iostream>

namespace riscv_emulator {

void Register::set_contents(bool updated_contents[REGISTER_BITS]) {
    for (int i = 0; i < REGISTER_BITS; i ++) {
        this->contents[i] = updated_contents[i];
    }
}

unsigned long Register::get_contents() {
    unsigned long val = 0;
    for (int i = 0; i < REGISTER_BITS; i++) {
        val += this->contents[i]*std::pow(2,i);
    }
    return val;
}

void Register::copy_contents(bool given_array[REGISTER_BITS]) {
    for (int i = 0; i < REGISTER_BITS; i++) {
        given_array[i] = this->contents[i];
    }
}

Register::Register() {
    // set value of register to all zero by default
    // still valid for zero register so this works
    for (int i = 0; i < REGISTER_BITS; i++) {
        this->contents[i] = 0;
    }
}


} // namespace riscv_emulator