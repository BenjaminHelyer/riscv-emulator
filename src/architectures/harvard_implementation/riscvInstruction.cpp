#include "include/riscvInstruction.h"
#include "include/rTypeInstruction.h"

#include <math.h>

#include <stdexcept>
#include <iostream>

namespace riscv_emulator {

void RiscvInstruction::set_pointer_from_type(char currType) {
    if (currType == 'R') {
        // we avoid object slicing here since we are using a pointer to get a sub-class
        // the important methods for the sub-class are all virtual, else they use the base class methods
        RTypeInstruction rInstruct(this->contents);
        this->typedInstruction = &rInstruct;
    }
    else if (currType == 'n') {
        // have this for testing purposes for now
        std::cout << "No type set for this instruction. Setting typedInstruction pointer to null." << std::endl;
        this->typedInstruction = NULL;
    }
    else {
        throw std::invalid_argument("unknown instruction type");
    }
}

void RiscvInstruction::set_opcode() {
    // zero the opcode, else it adds on the opcode from previous runs
    this->opcode = 0;
    for (int i = 0; i < 7; i++) {
        this->opcode += this->contents[i]*std::pow(2,i);
    }
}

void RiscvInstruction::set_type() {
    if(opcode == 0) {
        // null type which indicates there is no instruction
        this->type = 'n';
    }
}

void RiscvInstruction::set_contents(bool updated_contents[32]) {
    // upon changing the contents, the first thing we need to do is to deallocate the previous memory from the typed instruction
    delete this->typedInstruction;

    // now we actually change the contents of the instruction
    for (int i = 0; i < 32; i++) {
        this->contents[i] = updated_contents[i];
    }

    // update the instruction opcode and type
    this->set_opcode();
    this->set_type();

    // update the typed instruction based on the determined type
    this->set_pointer_from_type(this->type);
}

RiscvInstruction::RiscvInstruction() {
    std::cout << "IN DEFAULT CONSTRUCTOR FOR RISCVINSTRUCTION" << std::endl;
    bool all_zeroes[32] = { };
    this->set_contents(all_zeroes);
}

RiscvInstruction::~RiscvInstruction() {
    // deallocate the memory for the typed instruction
    delete this->typedInstruction;
}

} // namespace riscv_emulator