#include "include/controlUnit.h"

#include <math.h>

#include <stdexcept>
#include <iostream>

namespace riscv_emulator {

void ControlUnit::increment_pc() {
    bool pc_val[REGISTER_BITS];
    // copy the contents of the object pointed to by the ctrlPC pointer
    this->ctrlPC->copy_contents(pc_val);

    // now we increment the PC by one
    this->increment_bool(pc_val);

    this->ctrlPC->set_contents(pc_val);
}

void ControlUnit::increment_bool(bool bool_to_increment[REGISTER_BITS]) {
    int index = 0;
    while (bool_to_increment[index] != 0 && index < REGISTER_BITS) {
        index++;
    }
    if (index >= REGISTER_BITS ) {
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

void ControlUnit::add_to_bool(bool bool_to_add[REGISTER_BITS], unsigned int immediate) {
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
    int opcode = 0;
    opcode = ctrlInstruction.get_opcode();

    bool full_instr[32] = { };
    ctrlInstruction.copy_contents(full_instr);

    switch (opcode) {
        case 3:
            // opcode is for some I type instruction
        case 19:
            // opcode is for some I type instruction
        case 35:
            // opcode is for some S type instruction
        case 51:
            // opcode is for some R type instruction
        case 15:
            // opcode is for some I type instruction
        case 115:
            // opcode is for some I type instruction
        case 99:
            // opcode is for some B type instruction
        case 239:
            // opcode is for J jal
            // return after jump and do not increment program counter
            return;
        case 231:
            // opcode is for I jalr
        case 23:
            // opcode is for U auipc
        case 55:
            // opcode is for U lui
        default:
            throw std::invalid_argument("opcode of instruction not recognized");
            // return and do not increment program counter
            return;
    }

    // increment program counter at the very end, unless it was a jump instruction (covered above)
    this->increment_pc();
}

int ControlUnit::get_opcode_extend(bool instr_bool[32]) {
    int val = 0;
    for (int i = 12; i < 15; i++) {
        val += instr_bool[i]*std::pow(2, i);
    }
}

ControlUnit::ControlUnit() {
    // can add default constructor later
}

ControlUnit::~ControlUnit() {
    delete ctrlDataMem;
    delete ctrlPC;
    delete ctrlRegisters;
}

} // namespace riscv_emulator