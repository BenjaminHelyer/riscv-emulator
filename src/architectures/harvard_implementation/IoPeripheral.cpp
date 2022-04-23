#include "include/ioPeripheral.h"
#include "include/instructionMemory.h"
#include "include/dataMemory.h"

#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>

namespace riscv_emulator {

void IoPeripheral::write_instr_to_mem(std::string filename, InstructionMemory &instr_mem) {
    this->instr_stream.open(filename);
    if (instr_stream.is_open()) {
        int mem_addr = 0;
        bool my_instr_bool[32] = { };
        RiscvInstruction curr_instr;
        std::string file_line;

        while (std::getline(instr_stream, file_line)) {
            // set all the contents of the boolean array to zero just in case
            for (int i = 0; i < 32; i++) {
                my_instr_bool[i] = 0;
            }

            // first we copy the current line's instruction to a boolean array
            for (int i = 0; i < 32; i++) {
                if (file_line[i] == '1') {
                    my_instr_bool[i] = 1;
                }
                else if (file_line[i] == '0') {
                    my_instr_bool[i] = 0;
                }
                else {
                    std::cout << "character in line not recognized. character was: " << file_line[i] << std::endl;
                }
            }

            // finally we set the instruction memory at the current address to the contents of the boolean array
            curr_instr.set_contents(my_instr_bool);
            instr_mem.set_instruction(mem_addr, curr_instr);
            mem_addr++;
        }
        instr_stream.close();
    }
    else {
        throw std::invalid_argument("filename not found");
    }
}

void IoPeripheral::write_data_to_mem(std::string filename, DataMemory &data_mem) {

}

} // namespace riscv_emulator