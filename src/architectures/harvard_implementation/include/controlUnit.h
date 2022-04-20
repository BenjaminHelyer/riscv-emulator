#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include "dataMemory.h"
#include "instructionMemory.h"
#include "register.h"
#include "riscvInstruction.h"

namespace riscv_emulator {

class ControlUnit {
    public:
        // the control unit has pointers to all these so it can access them directly
        DataMemory *ctrlDataMem = nullptr;
        Register *ctrlPC = nullptr;
        Register *ctrlRegisters[32] = { nullptr };
        // the control unit doesn't need to access the instruction memory since it won't be messing with instructions, only with the program counter
        
        /*! \brief The function to call by which the control unit executes an instruction.
        *
        * Expected usage: processor hands the control unit an instruction via execute_instruction.
        * The control unit then handles setting the program counter for the next instruction
        * The control unit does not adjust the instruction memory; it is only handed one instruction at a time by the processor.
        * The control unit can affect the data memory, program counter, and all the other registers.
        */
        void execute_instruction(RiscvInstruction ctrlInstruction);
};

} // namespace riscv_emulator

#endif