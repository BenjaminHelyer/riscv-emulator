#include "include/instructionMemory.h"
#include "include/riscvInstruction.h"

namespace riscv_emulator {

void InstructionMemory::set_instruction(int address, RiscvInstruction updated_instruction) {
    bool updated_contents[32] = { };
    updated_instruction.copy_contents(updated_contents);
    this->instructions[address].set_contents(updated_contents);
}

RiscvInstruction InstructionMemory::get_instruction(int address) {
    RiscvInstruction found_instruction;
    bool found_contents[32] = { };
    
    this->instructions[address].copy_contents(found_contents);
    found_instruction.set_contents(found_contents);

    return found_instruction;
}

InstructionMemory::InstructionMemory() {
    bool all_zeroes[32] = { };
    RiscvInstruction zeroInstruction;
    zeroInstruction.set_contents(all_zeroes);

    for (int i = 0; i < INSTRUCTION_MEMORY_SIZE; i++) {
        this->set_instruction(i, zeroInstruction);
    }
}

} // namespace riscv_emulator