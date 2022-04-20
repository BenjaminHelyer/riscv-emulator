#ifndef INSTRUCTIONMEMORY_H
#define INSTRUCTIONMEMORY_H

#include "riscvInstruction.h"

namespace riscv_emulator {

const int INSTRUCTION_MEMORY_SIZE = 1000;

/*! \brief Class for the instruction memory, which holds RiscvInstruction objects and is of a certain size
*
*/
class InstructionMemory {
    private:
        RiscvInstruction instructions[INSTRUCTION_MEMORY_SIZE];
    public:
        /*! \brief Sets an instruction based on a given address and given RiscvInstruction object.
        *
        */
        void set_instruction(int address, RiscvInstruction updated_instruction);
        /*! \brief Returns an instruction at a particular address as a RiscvInstruction object.
        *
        */
        RiscvInstruction get_instruction(int address);
        /*! \brief The default constructor zeroes out all the instructions. This is valid because RISC-V does not have instructions equal to zero.
        *
        */
        InstructionMemory();
};

} // namespace riscv_emulator

#endif