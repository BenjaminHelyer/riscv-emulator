#include "include/rTypeInstruction.h"

#include <math.h>

namespace riscv_emulator {

void RTypeInstruction::set_rd() {
    for (int i = 7; i < 12; i++) {
        this->rd += this->contents[i]*std::pow(2,i - 7);
    }
}

void RTypeInstruction::set_funct3() {
    for (int i = 12; i < 15; i++) {
        this->funct3 += this->contents[i]*std::pow(2,i - 12);
    }
}

void RTypeInstruction::set_rs1() {
    for (int i = 15; i < 20; i++) {
        this->rs1 += this->contents[i]*std::pow(2,i - 15);
    }
}

void RTypeInstruction::set_rs2() {
    for (int i = 20; i < 25; i++) {
        this->rs2 += this->contents[i]*std::pow(2,i - 20);
    }
}

void RTypeInstruction::set_funct7() {
    for (int i = 25; i < 32; i++) {
        this->funct7 += this->contents[i]*std::pow(2,i - 25);
    }
}

void RTypeInstruction::set_contents(bool updated_contents[32]) {
    for (int i = 0; i < 32; i++) {
        this->contents[i] = updated_contents[i];
    }
    this->set_opcode();
    this->set_type();
    this->set_rd();
    this->set_funct3();
    this->set_rs1();
    this->set_rs2();
    this->set_funct7();
}

} // namespace riscv_emulator