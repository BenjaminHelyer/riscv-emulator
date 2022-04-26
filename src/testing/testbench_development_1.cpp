#include "../architectures/harvard_implementation/include/riscvInstruction.h"
#include "../architectures/harvard_implementation/include/dataMemory.h"
#include "../architectures/harvard_implementation/include/processor.h"
#include "../architectures/harvard_implementation/include/register.h"
#include "../architectures/harvard_implementation/include/instructionMemory.h"
#include "../architectures/harvard_implementation/include/controlUnit.h"
#include "../architectures/harvard_implementation/include/processor.h"
#include "../architectures/harvard_implementation/include/ioPeripheral.h"

#include <iostream>
#include <string>

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

    myInstruction.copy_bits(5, 9, test_array);

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

    myInstruction.copy_bits(20, 29, test_array_2);

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

void processor_tests_1() {
    riscv_emulator::Processor myProcessor;

    // do this manually for now, will add I/O later
    // mostly just want to test LUI instruction for now
    // this will also test the overall ControlUnit sequence
    bool my_lui_1[32] = { };
    // opcode = 1110110
    my_lui_1[0] = 1;
    my_lui_1[1] = 1;
    my_lui_1[2] = 1;
    my_lui_1[3] = 0;
    my_lui_1[4] = 1;
    my_lui_1[5] = 1;
    my_lui_1[6] = 0;
    // rd = 00100
    my_lui_1[7] = 0;
    my_lui_1[8] = 0;
    my_lui_1[9] = 1;
    my_lui_1[10] = 0;
    my_lui_1[11] = 0;
    // imm[31:12] = 0110...0
    my_lui_1[12] = 0;
    my_lui_1[13] = 1;
    my_lui_1[14] = 1;
    my_lui_1[15] = 1;
    my_lui_1[16] = 0;
    my_lui_1[17] = 0;
    my_lui_1[18] = 0;
    my_lui_1[19] = 0;
    my_lui_1[20] = 0;
    my_lui_1[21] = 0;
    my_lui_1[22] = 0;
    my_lui_1[23] = 0;
    my_lui_1[24] = 0;
    my_lui_1[25] = 0;
    my_lui_1[26] = 0;
    my_lui_1[27] = 0;
    my_lui_1[28] = 0;
    my_lui_1[29] = 0;
    my_lui_1[30] = 0;
    my_lui_1[31] = 0;

    std::cout << "Boolean array my_lui_1 is (lsb on left): ";
    for (int i = 0; i < 32; i++) {
        std::cout << my_lui_1[i];
    }
    std::cout << std::endl;

    riscv_emulator::RiscvInstruction my_lui_instr_1;
    my_lui_instr_1.set_contents(my_lui_1);

    bool inst_test_array_1[32] = { };
    my_lui_instr_1.copy_contents(inst_test_array_1);

    std::cout << "Instruction my_lui_instr_1 is (lsb on left): ";
    for (int i = 0; i < 32; i++) {
        std::cout << inst_test_array_1[i];
    }
    std::cout << std::endl;

    myProcessor.instrMem.set_instruction(0, my_lui_instr_1);

    riscv_emulator::RiscvInstruction instr_confirm;
    instr_confirm = myProcessor.instrMem.get_instruction(0);

    bool inst_test_array_2[32] = { };
    instr_confirm.copy_contents(inst_test_array_2);

    std::cout << "Instruction at instrMem address 0 is (lsb on left): ";
    for (int i = 0; i < 32; i++) {
        std::cout << inst_test_array_2[i];
    }
    std::cout << std::endl;

    bool reg_test_array_1[32] = { };
    myProcessor.registers[4].copy_contents(reg_test_array_1);

    std::cout << "Register 4 value before running processor: ";
    for (int i = 0; i < 32; i ++) {
        std::cout << reg_test_array_1[i];
    }
    std::cout << std::endl;

    // in theory pc should be initialized to zero, so we shouldn't need to do anything to it to run the processor
    myProcessor.run_processor();

    bool reg_test_array_2[32] = { };
    myProcessor.registers[4].copy_contents(reg_test_array_2);

    std::cout << "Register 4 value after running processor: ";
    for (int i = 0; i < 32; i ++) {
        std::cout << reg_test_array_2[i];
    }
    std::cout << std::endl;

    std::cout << "Adding an instruction and running processor again..." << std::endl;

    bool my_i_addi_1[32] = { };
    // let's only change the bits to 1 that we need to change to 1
    // opcode field
    my_i_addi_1[0] = 1;
    my_i_addi_1[1] = 1;
    my_i_addi_1[4] = 1;
    // rd field = 00100
    my_i_addi_1[9] = 1;
    // opcode extend field = 0
    // rs1 field = 00100
    my_i_addi_1[17] = 1;
    // imm field = 0001
    my_i_addi_1[23] = 1;

    std::cout << "Boolean array my_i_addi_1 is (lsb on left): ";
    for (int i = 0; i < 32; i++) {
        std::cout << my_i_addi_1[i];
    }
    std::cout << std::endl;

    riscv_emulator::RiscvInstruction my_i_addi_instr_1;
    my_i_addi_instr_1.set_contents(my_i_addi_1);

    myProcessor.instrMem.set_instruction(1, my_i_addi_instr_1);

    myProcessor.registers[4].copy_contents(reg_test_array_1);

    std::cout << "Register 4 value before running processor: ";
    for (int i = 0; i < 32; i ++) {
        std::cout << reg_test_array_1[i];
    }
    std::cout << std::endl;

    // in theory pc should be initialized to zero, so we shouldn't need to do anything to it to run the processor
    myProcessor.run_processor();

    myProcessor.registers[4].copy_contents(reg_test_array_2);

    std::cout << "Register 4 value after running processor: ";
    for (int i = 0; i < 32; i ++) {
        std::cout << reg_test_array_2[i];
    }
    std::cout << std::endl;

}

void io_tests() {
    std::cout << "Beginning I/O tests..." << std::endl;

    riscv_emulator::IoPeripheral my_io;
    riscv_emulator::InstructionMemory my_instr_mem;

    std::string filename = "src/testing/test_01.txt";

    my_io.write_instr_to_mem(filename, my_instr_mem);

    riscv_emulator::RiscvInstruction curr_instr;
    int curr_addr = 0;
    curr_instr = my_instr_mem.get_instruction(curr_addr);
    while (curr_instr.get_opcode() != 0) {
        std::cout << "Instruction at address " << curr_addr << " is: ";
        bool my_out_bool[32] = { };
        curr_instr.copy_contents(my_out_bool);
        for (int i = 0; i < 32; i++) {
            std::cout << my_out_bool[i];
        }
        std::cout << std::endl;

        curr_addr++;
        curr_instr = my_instr_mem.get_instruction(curr_addr);
    }
}

void processor_tests_2() {
    std::cout << "Beginning processor_tests_2..." << std::endl;

    riscv_emulator::Processor myProcessor;
    std::string my_file = "src/testing/test_01.txt";

    bool my_reg_contents[32] = { };
    myProcessor.registers[4].copy_contents(my_reg_contents);

    std::cout << "Contents of Reg 4 before running processor: ";
    for (int i = 0; i < 32; i++) {
        std::cout << my_reg_contents[i];
    }
    std::cout << std::endl;

    myProcessor.registers[5].copy_contents(my_reg_contents);

    std::cout << "Contents of Reg 5 before running processor: ";
    for (int i = 0; i < 32; i++) {
        std::cout << my_reg_contents[i];
    }
    std::cout << std::endl;

    myProcessor.registers[6].copy_contents(my_reg_contents);

    std::cout << "Contents of Reg 6 before running processor: ";
    for (int i = 0; i < 32; i++) {
        std::cout << my_reg_contents[i];
    }
    std::cout << std::endl;

    myProcessor.registers[7].copy_contents(my_reg_contents);

    std::cout << "Contents of Reg 7 before running processor: ";
    for (int i = 0; i < 32; i++) {
        std::cout << my_reg_contents[i];
    }
    std::cout << std::endl;

    myProcessor.load_instructions_from_file(my_file);
    myProcessor.run_processor();

    myProcessor.registers[4].copy_contents(my_reg_contents);

    std::cout << "Contents of Reg 4 after running processor: ";
    for (int i = 0; i < 32; i++) {
        std::cout << my_reg_contents[i];
    }
    std::cout << std::endl;

    myProcessor.registers[5].copy_contents(my_reg_contents);

    std::cout << "Contents of Reg 5 after running processor: ";
    for (int i = 0; i < 32; i++) {
        std::cout << my_reg_contents[i];
    }
    std::cout << std::endl;

    myProcessor.registers[6].copy_contents(my_reg_contents);

    std::cout << "Contents of Reg 6 after running processor: ";
    for (int i = 0; i < 32; i++) {
        std::cout << my_reg_contents[i];
    }
    std::cout << std::endl;

    myProcessor.registers[7].copy_contents(my_reg_contents);

    std::cout << "Contents of Reg 7 after running processor: ";
    for (int i = 0; i < 32; i++) {
        std::cout << my_reg_contents[i];
    }
    std::cout << std::endl;
}

int main() {

    //instruction_tests();

    //data_mem_tests();

    //reg_tests();

    //instr_mem_tests();

    //control_unit_tests();

    //processor_tests_1();

    //io_tests();

    processor_tests_2();

    return 0;
}