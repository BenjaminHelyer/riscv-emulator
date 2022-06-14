#include "architectures/harvard_implementation/include/riscvInstruction.h"
#include "architectures/harvard_implementation/include/dataMemory.h"
#include "architectures/harvard_implementation/include/processor.h"
#include "architectures/harvard_implementation/include/register.h"
#include "architectures/harvard_implementation/include/instructionMemory.h"
#include "architectures/harvard_implementation/include/controlUnit.h"
#include "architectures/harvard_implementation/include/processor.h"
#include "architectures/harvard_implementation/include/ioPeripheral.h"
#include "interface/command_line/include/commands.h"

#include <iostream>
#include <string>

int main() {
    riscv_emulator::Commands userCommandInterface;

    userCommandInterface.run_interface();

    return 0;
}