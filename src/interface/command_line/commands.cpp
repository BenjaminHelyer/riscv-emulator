#include "include/commands.h"
#include "../../architectures/harvard_implementation/include/riscvInstruction.h"
#include "../../architectures/harvard_implementation/include/dataMemory.h"
#include "../../architectures/harvard_implementation/include/processor.h"
#include "../../architectures/harvard_implementation/include/register.h"
#include "../../architectures/harvard_implementation/include/instructionMemory.h"
#include "../../architectures/harvard_implementation/include/controlUnit.h"
#include "../../architectures/harvard_implementation/include/processor.h"
#include "../../architectures/harvard_implementation/include/ioPeripheral.h"

#include <iostream>
#include <string>

namespace riscv_emulator {

void Commands::run_interface() {
    while (!(this->stop_process)) {
        std::cout << "Please enter a command. Enter 'HELP' for help." << std::endl;
        this->stop_process = 1;
    }

    // return when stop_process is pulled high
    return;
}

Commands::Commands() {
    // add in default constructor later if needed
}

} // namespace riscv_emulator
