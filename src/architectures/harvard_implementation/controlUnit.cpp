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
        // case where the bool value is 111...111, i.e, bool = -1 if sign extended
        // in this case, we don't want to throw an exception (since RISC-V doesn't use overflow)
        // just set the bool to zero
        for (int i = 0; i < REGISTER_BITS; i++) {
            bool_to_increment[i] = 0;
        }
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

    switch (opcode) {
        case 3:
            // opcode is for some I type instruction
            extend_op = get_opcode_extend(ctrlInstruction);
            switch (extend_op) {
                case 0:
                    // I lb instruction
                    break;
                case 1:
                    // I lh instruction
                    break;
                case 2:
                    // I lw instruction
                    break;
                case 4:
                    // I lbu instruction
                    break;
                case 5:
                    // I lhu instruction
                    break;
                default:
                    throw std::invalid_argument("extended opcode not recognized");
                    return;
            }
            break;
        case 19:
            // opcode is for some I type instruction
            extend_op = get_opcode_extend(ctrlInstruction);
            switch (extend_op) {
                case 0:
                    // I addi instruction
                    i_addi(ctrlInstruction);
                    break;
                case 2:
                    // I slti instruction
                    break;
                case 3:
                    // I sltiu instruction
                    break;
                case 4:
                    // I xori instruction
                    break;
                case 6:
                    // I ori instruction
                    break;
                case 7:
                    // I andi instruction
                    break;
                default:
                    throw std::invalid_argument("extended opcode not recognized");
                    return;
            }
            break;
        case 35:
            // opcode is for some S type instruction
            extend_op = get_opcode_extend(ctrlInstruction);
            switch (extend_op) {
                case 0:
                    // S sb instruction
                    break;
                case 1:
                    // S sh instruction
                    break;
                case 2:
                    // S sw instruction
                    break;
                default:
                    throw std::invalid_argument("extended opcode not recognized");
                    return;
            }
            break;
        case 51:
            // opcode is for some R type instruction
            extend_op = get_opcode_extend(ctrlInstruction);
            switch (extend_op) {
                case 0:
                    // NEED TO DETERMINE IF ADD OR SUB AFTER THIS
                    break;
                case 1:
                    // R sll instruction
                    break;
                case 2:
                    // R slt instruction
                    break;
                case 3:
                    // R sltu instruction
                    break;
                case 4:
                    // R xor instruction
                    break;
                case 5:
                    // NEED TO DETERMINE IF SRA OR SRL AFTER THIS
                    break;
                case 6:
                    // R or instruction
                    break;
                case 7:
                    // R and instruction
                    break;
                default:
                    throw std::invalid_argument("extended opcode not recognized");
                    return;
            }
            break;
        case 15:
            // opcode is for some I type instruction
            extend_op = get_opcode_extend(ctrlInstruction);
            switch (extend_op) {
                case 0:
                    // I fence instruction
                    break;
                case 1:
                    // I fence.i instruction
                    break;
                default:
                    throw std::invalid_argument("extended opcode not recognized");
                    return;
            }
            break;
        case 115:
            // opcode is for some I type instruction
            extend_op = get_opcode_extend(ctrlInstruction);
            switch (extend_op) {
                case 0:
                    // NEED TO DETERMINE DIFFERENCE BETWEEN ECALL AND EBREAK
                    break;
                case 1:
                    // I csrrw instruction
                    break;
                case 2:
                    // I csrrs instruction
                    break;
                case 3:
                    // I csrrc instruction
                    break;
                case 5:
                    // I csrrwi instruction
                    break;
                case 6:
                    // I csrrsi instruction
                    break;
                case 7:
                    // I csrrci instruction
                    break;
                default:
                    throw std::invalid_argument("extended opcode not recognized");
                    return;
            }
            break;
        case 99:
            // opcode is for some B type instruction
            extend_op = get_opcode_extend(ctrlInstruction);
            switch (extend_op) {
                case 0:
                    // B beq instruction
                    break;
                case 1:
                    // B bne instruction
                    break;
                case 4:
                    // B blt instruction
                    break;
                case 5:
                    // B bge instruction
                    break;
                case 6:
                    // B bltu instruction
                    break;
                case 7:
                    // B bgeu instruction
                    break;
                default:
                    throw std::invalid_argument("extended opcode not recognized");
                    return;
            }
            break;
        case 239:
            // opcode is for J jal
            // return after jump and do not increment program counter
            return;
        case 231:
            // opcode is for I jalr
            break;
        case 23:
            // opcode is for U auipc
            break;
        case 55:
            // opcode is for U lui
            u_lui(ctrlInstruction);
            break;
        default:
            throw std::invalid_argument("opcode of instruction not recognized");
            // return and do not increment program counter
            return;
    }

    // increment program counter at the very end, unless it was a jump instruction (covered above)
    this->increment_pc();
}

int ControlUnit::get_opcode_extend(RiscvInstruction instr) {
    // first copy the extended opcode into an array
    bool op_extend_array[3] = { };
    instr.copy_bits(12, 14, op_extend_array);

    int val = 0;
    for (int i = 0; i < 3; i++) {
        val += op_extend_array[i]*std::pow(2, i);
    }

    return val;
}

int ControlUnit::get_rd(RiscvInstruction instr) {
    // first copy the rd value into an array
    bool rd_bool_array[5] = { };
    instr.copy_bits(7, 11, rd_bool_array);

    int val = 0;
    for (int i = 0; i < 5; i++) {
        val += rd_bool_array[i]*std::pow(2, i);
    }

    return val;
}

int ControlUnit::get_rs1(RiscvInstruction instr) {
    bool rs1_bool_array[5] = { };
    instr.copy_bits(15, 19, rs1_bool_array);

    int val = 0;
    for (int i = 0; i < 5; i++) {
        val += rs1_bool_array[i]*std::pow(2, i);
    }

    return val;
}


// Begin functions for overall instructions

void ControlUnit::u_lui(RiscvInstruction instr) {
    int rd = 0;
    rd = get_rd(instr);

    // copy the contents of the register into an array, replace the 20 msbs with the values in the instruction, then set the contents of the register to this array
    // in this way, the 12 lsbs of the register contents will be unaffected by this instruction
    bool updated_reg_contents[32] = { };
    this->ctrlRegisters[rd]->copy_contents(updated_reg_contents);

    bool upper_20_bits[20] = { };
    instr.copy_bits(12, 31, upper_20_bits);

    int index_upper_20_bits = 0;
    for (int i = 12; i <= 31; i++) {
        updated_reg_contents[i] = upper_20_bits[index_upper_20_bits];
        index_upper_20_bits++;
    }

    this->ctrlRegisters[rd]->set_contents(updated_reg_contents);
}

void ControlUnit::i_addi(RiscvInstruction instr) {
    // get all the relevent values (rd, rs1, and the upper 12 bits for the immediate)
    int rd = 0;
    rd = get_rd(instr);

    int rs1 = 0;
    rs1 = get_rs1(instr);

    bool upper_12_bits[12] = { };
    instr.copy_bits(20, 31, upper_12_bits);
    
    // convert upper_12_bits to an int so that we can easily increment the array
    // we can use an int here since we're only using 12 bits
    int imm_val = 0;
    for (int i = 0; i < 12; i++) {
        imm_val += upper_12_bits[i]*std::pow(2, i);
    }

    // copy the conents of rs1, add the immediate to these contents, then save these contents to the destination register
    bool updated_reg_contents[32] = { };
    this->ctrlRegisters[rs1]->copy_contents(updated_reg_contents);
    
    add_to_bool(updated_reg_contents, imm_val);
    // now updated_reg_contents contains the value to be saved to the destination register

    // we don't care what the destination register had in it before, so just store the updated value
    this->ctrlRegisters[rd]->set_contents(updated_reg_contents);
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