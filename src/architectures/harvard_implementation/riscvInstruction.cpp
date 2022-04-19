#include "include/riscvInstruction.h"

#include <math.h>

namespace riscv_emulator {

void RiscvInstruction::set_opcode() {
    // set opcode equal to zero at the start so we don't add opcodes of previous runs
    this->opcode = 0;
    for (int i = 0; i < 7; i++) {
        this->opcode += this->contents[i]*std::pow(2,i);
    }
}

void RiscvInstruction::set_type() {
    // do nothing for now, will later set type based on opcode
}

void RiscvInstruction::set_contents(bool updated_contents[32]) {
    for (int i = 0; i < 32; i++) {
        this->contents[i] = updated_contents[i];
    }
    this->set_opcode();
    this->set_type();
}

void RiscvInstruction::copy_contents(bool input_array[32]) {
    for (int i = 0; i < 32; i++) {
        input_array[i] = this->contents[i];
    }
}

RiscvInstruction::RiscvInstruction() {
    // add in default constructor specifications later if needed
}

} // namespace riscv_emulator