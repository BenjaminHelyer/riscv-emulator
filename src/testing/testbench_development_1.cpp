#include "../architectures/harvard_implementation/include/riscvInstruction.h"
#include "../architectures/harvard_implementation/include/dataMemory.h"
#include "../architectures/harvard_implementation/include/processor.h"
#include "../architectures/harvard_implementation/include/register.h"

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

    bool testArray[32] = { };

    std::cout << "Original array seen as: ";
    for (int i = 0; i < 32; i++) {
        std::cout << testArray[i];
    }
    std::cout << std::endl;

    myInstruction.copy_contents(testArray);
    std::cout << "New array seen as: ";
    for (int i = 0; i < 32; i++) {
        std::cout << testArray[i];
    }
    std::cout << std::endl;

    bool testSmallerArray[25] = { };

    std::cout << "Smaller original array seen as: ";
    for (int i = 0; i < 25; i++) {
        std::cout << testSmallerArray[i];
    }
    std::cout << std::endl;

    myInstruction.copy_contents(testSmallerArray);
    std::cout << "Smaller new array seen as: ";
    for (int i = 0; i < 25; i++) {
        std::cout << testSmallerArray[i];
    }
    std::cout << std::endl;

}

void data_mem_tests() {
    std::cout << "Beginning data memory tests..." << std::endl;

    bool all_ones[riscv_emulator::CACHE_BITS_PER_ADDRESS];
    for (int i = 0; i < riscv_emulator::CACHE_BITS_PER_ADDRESS; i++) {
        all_ones[i] = 1;
    }
    int myAddress = 30;

    std::cout << "Setting contents of memory at address " << myAddress << " to: ";
    for (int i = 0; i < riscv_emulator::CACHE_BITS_PER_ADDRESS; i++) {
        std::cout << all_ones[i];
    }
    std::cout << std::endl;

    riscv_emulator::DataMemory myData;
    std::cout << "CONTENTS[" << myAddress << "] before memory set: " << myData.get_cache_val(myAddress) << std::endl;

    myData.set_cache_val(myAddress, all_ones);

    std::cout << "CONTENTS[" << myAddress << "] after memory set: ";
    bool copied_array[riscv_emulator::CACHE_BITS_PER_ADDRESS] = { };
    myData.copy_cache_val(myAddress, copied_array);
    for (int i = 0; i < riscv_emulator::CACHE_BITS_PER_ADDRESS; i++) {
        std::cout << copied_array[i];
    }
    std::cout << std::endl;

    std::cout << "CONTENTS[" << myAddress << "] as an integer after memory set: " << myData.get_cache_val(myAddress) << std::endl;
    
}

void reg_tests () {
    std::cout << "Beginning register tests..." << std::endl;

    bool all_ones[riscv_emulator::REGISTER_BITS];
    for (int i = 0; i < riscv_emulator::REGISTER_BITS; i++) {
        all_ones[i] = 1;
    }

    std::cout << "Setting contents of register to: ";
    for (int i = 0; i < riscv_emulator::REGISTER_BITS; i++) {
        std::cout << all_ones[i];
    }
    std::cout << std::endl;

    riscv_emulator::Register myRegister;
    std::cout << "CONTENTS[myRegister] before set: " << myRegister.get_contents() << std::endl;

    myRegister.set_contents(all_ones);

    bool copied_array[riscv_emulator::REGISTER_BITS];
    std::cout << "CONTENTS[myRegister] after set: ";
    myRegister.copy_contents(copied_array);
    for (int i = 0; i < riscv_emulator::REGISTER_BITS; i++) {
        std::cout << copied_array[i];
    }
    std::cout << std::endl;

    unsigned long reg_val;
    reg_val = myRegister.get_contents();
    std::cout << "CONTENTS[myRegister] as a long after set: " << reg_val << std::endl;


}

int main() {

    instruction_tests();

    data_mem_tests();

    reg_tests();

    return 0;
}