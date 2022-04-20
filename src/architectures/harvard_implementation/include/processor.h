#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "instructionMemory.h"
#include "register.h"
#include "riscvInstruction.h"
#include "dataMemory.h"
#include "controlUnit.h"

namespace riscv_emulator {

class Processor {
    // strictly speaking, a struct should probably be used here since everything is public, but classes have been used for everything else, so we'll stick with a class
    public:
        InstructionMemory instrMem;
        DataMemory dataMem;
        Register pc;
        Register registers[32]; // holds all registers other than the pc, including the zero register
        // may want to find a way to hold the zero register value as constant or static at some point

        void run_processor();

        Processor();
};

} // namespace riscv_emulator

#endif