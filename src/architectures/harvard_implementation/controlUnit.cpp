#include "include/controlUnit.h"

#include <stdexcept>
#include <iostream>

namespace riscv_emulator {

void ControlUnit::increment_bool(bool bool_to_increment[32]) {
    int index = 0;
    while (bool_to_increment[index] != 0 && index < 32) {
        index++;
    }
    if (index >= 32 ) {
        throw std::invalid_argument("boolean array already at it's maximum value!");
    }
    else if (index == 0) {
        bool_to_increment[0] = 1;
    }
    else {
        bool_to_increment[index] = 1;
        for (int i = index - 1; i >= 0; i--) {
            bool_to_increment[i] = 0;
        }
    }
}

void ControlUnit::add_to_bool(bool bool_to_add[32], unsigned int immediate) {
    unsigned int index = 0;
    if (immediate == 0) {
        return;
    }
    else {
        while (index < immediate) {
            increment_bool(bool_to_add);
            index++;
        }
    }
}

void ControlUnit::execute_instruction(RiscvInstruction ctrlInstruction) {
    // need to increment the program counter register if not otherwise adjusting it
}

ControlUnit::ControlUnit() {
    // can add default constructor later
}

} // namespace riscv_emulator