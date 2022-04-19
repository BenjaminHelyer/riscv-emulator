#include "../architectures/harvard_implementation/include/riscvInstruction.h"
#include "../architectures/harvard_implementation/include/rTypeInstruction.h"
#include "../architectures/harvard_implementation/include/data.h"
#include "../architectures/harvard_implementation/include/processor.h"

#include <iostream>

void instruction_tests() {
    std::cout << "Beginning instruction tests..." << std::endl;

    bool all_ones[32];
    for (int i = 0; i < 32; i++) {
        all_ones[i] = 1;
    }

    std::cout << "Setting contents of instruction to: ";
    for (int i = 0; i < 32; i++) {
        std::cout << all_ones[i];
    }
    std::cout << std::endl;
    
    riscv_emulator::RiscvInstruction myInstruction;
    myInstruction.set_contents(all_ones);

    int my_opcode = myInstruction.get_opcode();
    std::cout << "Opcode seen as: " << my_opcode << std::endl;
    if (my_opcode == 127) {
        std::cout << "Opcode test passed." << std::endl;
    }
    else {
        std::cout << "Opcode test failed." << std::endl;
    }

    std::cout << "Trying to set an R-Type instruction to all ones..." << std::endl;

    riscv_emulator::RTypeInstruction myRType;
    std::cout << "Successfully instantiated R-Type object from default constructor." << std::endl;
    myRType.set_contents(all_ones);

    int my_rd = myRType.get_rd();
    std::cout << "rd seen as: " << my_rd << std::endl;


}

int main() {

    instruction_tests();

    return 0;
}