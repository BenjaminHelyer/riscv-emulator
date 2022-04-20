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

    int extend_op = 0;

    bool full_instr[32] = { };
    ctrlInstruction.copy_contents(full_instr);

    switch (opcode) {
        case 3:
            // opcode is for some I type instruction
            extend_op = get_opcode_extend(full_instr);
            switch (extend_op) {
                case 0:
                    // I lb instruction
                case 1:
                    // I lh instruction
                case 2:
                    // I lw instruction
                case 4:
                    // I lbu instruction
                case 5:
                    // I lhu instruction
                default:
                    throw std::invalid_argument("extended opcode not recognized");
                    return;
            }
        case 19:
            // opcode is for some I type instruction
            extend_op = get_opcode_extend(full_instr);
            switch (extend_op) {
                case 0:
                    // I addi instruction
                case 2:
                    // I slti instruction
                case 3:
                    // I sltiu instruction
                case 4:
                    // I xori instruction
                case 6:
                    // I ori instruction
                case 7:
                    // I andi instruction
                default:
                    throw std::invalid_argument("extended opcode not recognized");
                    return;
            }
        case 35:
            // opcode is for some S type instruction
            extend_op = get_opcode_extend(full_instr);
            switch (extend_op) {
                case 0:
                    // S sb instruction
                case 1:
                    // S sh instruction
                case 2:
                    // S sw instruction
                default:
                    throw std::invalid_argument("extended opcode not recognized");
                    return;
            }
        case 51:
            // opcode is for some R type instruction
            extend_op = get_opcode_extend(full_instr);
            switch (extend_op) {
                case 0:
                    // NEED TO DETERMINE IF ADD OR SUB AFTER THIS
                case 1:
                    // R sll instruction
                case 2:
                    // R slt instruction
                case 3:
                    // R sltu instruction
                case 4:
                    // R xor instruction
                case 5:
                    // NEED TO DETERMINE IF SRA OR SRL AFTER THIS
                case 6:
                    // R or instruction
                case 7:
                    // R and instruction
                default:
                    throw std::invalid_argument("extended opcode not recognized");
                    return;
            }
        case 15:
            // opcode is for some I type instruction
            extend_op = get_opcode_extend(full_instr);
            switch (extend_op) {
                case 0:
                    // I fence instruction
                case 1:
                    // I fence.i instruction
                default:
                    throw std::invalid_argument("extended opcode not recognized");
                    return;
            }
        case 115:
            // opcode is for some I type instruction
            extend_op = get_opcode_extend(full_instr);
            switch (extend_op) {
                case 0:
                    // NEED TO DETERMINE DIFFERENCE BETWEEN ECALL AND EBREAK
                case 1:
                    // I csrrw instruction
                case 2:
                    // I csrrs instruction
                case 3:
                    // I csrrc instruction
                case 5:
                    // I csrrwi instruction
                case 6:
                    // I csrrsi instruction
                case 7:
                    // I csrrci instruction
                default:
                    throw std::invalid_argument("extended opcode not recognized");
                    return;
            }
        case 99:
            // opcode is for some B type instruction
            extend_op = get_opcode_extend(full_instr);
            switch (extend_op) {
                case 0:
                    // B beq instruction
                case 1:
                    // B bne instruction
                case 4:
                    // B blt instruction
                case 5:
                    // B bge instruction
                case 6:
                    // B bltu instruction
                case 7:
                    // B bgeu instruction
                default:
                    throw std::invalid_argument("extended opcode not recognized");
                    return;
            }
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