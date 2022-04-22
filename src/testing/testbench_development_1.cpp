#include "../architectures/harvard_implementation/include/riscvInstruction.h"
#include "../architectures/harvard_implementation/include/dataMemory.h"
#include "../architectures/harvard_implementation/include/processor.h"
#include "../architectures/harvard_implementation/include/register.h"
#include "../architectures/harvard_implementation/include/instructionMemory.h"
#include "../architectures/harvard_implementation/include/controlUnit.h"
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

    bool test_array[5] = { };

    int my_size = 0;
    my_size = 1 + sizeof(test_array) / sizeof(test_array[0]);
    std::cout << "my_size = " << my_size << std::endl;

    std::cout << "test_array original array seen as: ";
    for (int i = 0; i < 5; i++) {
        std::cout << test_array[i];
    }
    std::cout << std::endl;

    myInstruction.get_bits(5, 9, test_array);

    std::cout << "Specific get bits function results in array: ";
    for (int i = 0; i < 5; i++) {
        std::cout << test_array[i];
    }
    std::cout << std::endl;

    bool test_array_2[10] = { };
    test_array_2[6] = 1;

    my_size = 1 + sizeof(test_array_2) / sizeof(test_array_2[0]);
    std::cout << "my_size = " << my_size << std::endl;

    std::cout << "test_array_2 original array seen as: ";
    for (int i = 0; i < 10; i++) {
        std::cout << test_array_2[i];
    }
    std::cout << std::endl;

    myInstruction.get_bits(20, 29, test_array_2);

    std::cout << "Specific get bits function results in array: ";
    for (int i = 0; i < 10; i++) {
        std::cout << test_array_2[i];
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

void instr_mem_tests() {
    std::cout << "Beginning instruction memory tests..." << std::endl;

    riscv_emulator::InstructionMemory myInstrMem;

    std::cout << "Contents of the first twenty instructions before setting the instruction memory:" << std::endl;
    for (int i = 0; i < 20; i++) {
        riscv_emulator::RiscvInstruction myInstruction;
        bool curr_instruction[32];
        myInstruction = myInstrMem.get_instruction(i);
        myInstruction.copy_contents(curr_instruction);
        std::cout << "InstructionMemory[" << i << "]: ";
        for (int j = 0; j < 32; j++) {
            std::cout << curr_instruction[j];
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < 10; i++) {
        riscv_emulator::RiscvInstruction myInstruction;
        bool curr_instruction[32] = { };
        curr_instruction[i] = 1;
        myInstruction.set_contents(curr_instruction);
        myInstrMem.set_instruction(i, myInstruction);
    }

    std::cout << "Contents of the first twenty instructions after setting the instruction memory:" << std::endl;
    for (int i = 0; i < 20; i++) {
        riscv_emulator::RiscvInstruction myInstruction;
        bool curr_instruction[32];
        myInstruction = myInstrMem.get_instruction(i);
        myInstruction.copy_contents(curr_instruction);
        std::cout << "InstructionMemory[" << i << "]: ";
        for (int j = 0; j < 32; j++) {
            std::cout << curr_instruction[j];
        }
        std::cout << std::endl;
    }

    std::cout << "Ending instruction memory tests." << std::endl;
}

void control_unit_tests() {
    std::cout << "Beginning control unit tests..." << std::endl;

    riscv_emulator::ControlUnit myCtrlUnit;

    bool myBool[riscv_emulator::REGISTER_BITS] = { };
    
    std::cout << "bool[32] before incrementing: ";
    for (int i = 0; i < 32; i++) {
        std::cout << myBool[i];
    }
    std::cout << std::endl;

    myCtrlUnit.increment_bool(myBool);

    std::cout << "bool[32] after incrementing: ";
    for (int i = 0; i < 32; i++) {
        std::cout << myBool[i];
    }
    std::cout << std::endl;

    myCtrlUnit.increment_bool(myBool);

    std::cout << "bool[32] after incrementing: ";
    for (int i = 0; i < 32; i++) {
        std::cout << myBool[i];
    }
    std::cout << std::endl;

    myCtrlUnit.increment_bool(myBool);

    std::cout << "bool[32] after incrementing: ";
    for (int i = 0; i < 32; i++) {
        std::cout << myBool[i];
    }
    std::cout << std::endl;

    myCtrlUnit.increment_bool(myBool);

    std::cout << "bool[32] after incrementing: ";
    for (int i = 0; i < 32; i++) {
        std::cout << myBool[i];
    }
    std::cout << std::endl;

    unsigned int immediate = 5;
    myCtrlUnit.add_to_bool(myBool, immediate);

    std::cout << "Adding " << immediate << " to bool[32] yields: ";
    for (int i = 0; i < 32; i++) {
        std::cout << myBool[i];
    }
    std::cout << std::endl;

    immediate = 6;
    myCtrlUnit.add_to_bool(myBool, immediate);

    std::cout << "Adding " << immediate << " to bool[32] yields: ";
    for (int i = 0; i < 32; i++) {
        std::cout << myBool[i];
    }
    std::cout << std::endl;

    immediate = 32;
    myCtrlUnit.add_to_bool(myBool, immediate);

    std::cout << "Adding " << immediate << " to bool[32] yields: ";
    for (int i = 0; i < 32; i++) {
        std::cout << myBool[i];
    }
    std::cout << std::endl;

    riscv_emulator::Register testPC;
    bool pc_bool[riscv_emulator::REGISTER_BITS] = { };
    testPC.set_contents(pc_bool);

    std::cout << "testPC before incrementing: " << testPC.get_contents() << std::endl;

    myCtrlUnit.ctrlPC = &testPC;

    myCtrlUnit.increment_pc();

    std::cout << "testPC after incrementing: " << testPC.get_contents() << std::endl;

    myCtrlUnit.increment_pc();

    std::cout << "testPC after incrementing: " << testPC.get_contents() << std::endl;

    myCtrlUnit.increment_pc();

    std::cout << "testPC after incrementing: " << testPC.get_contents() << std::endl;
}

int main() {

    instruction_tests();

    //data_mem_tests();

    //reg_tests();

    //instr_mem_tests();

    //control_unit_tests();

    return 0;
}