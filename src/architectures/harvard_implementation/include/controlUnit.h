#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include "dataMemory.h"
#include "instructionMemory.h"
#include "register.h"
#include "riscvInstruction.h"

namespace riscv_emulator {

class ControlUnit {
    private:
        /*! \brief Gets the extended opcode for a boolean array representing an instruction.
        *
        * Not implemented in RiscvInstruction class since not all instructions have an extended opcode.
        * Once the processor sees that this instruction is of a type with an extended opcode, it gets the extended opcode.
        * Similar to other functions, the basis for the interface between this function and the RiscvInstruction object is the copy_bits function.
        */
        int get_opcode_extend(RiscvInstruction instr);

    public:
        /*! \brief Increments the PC by copying the contents of the PC then incrementing the resulting boolean array.
        *
        */
        void increment_pc();
        /*! \brief Function for incrementing a boolean array. Note that this function alters the array that is passed to it.
        *
        * Implemented addition in this way because the average runtime for incrementing an array in this way is better than converting a boolean array to an int then converting the int back into an array.
        * In fact, for converting a boolean array to an int, the runtime would consistently be the length of the array.
        * Thus, the runtime for converting an array to an int and back again would be twice the worst-case runtime for addition in this method.
        */
        void increment_bool(bool bool_to_increment[REGISTER_BITS]);
        /*! \brief Function for adding an immediate value to a boolean array. Note that this function alters the array that is passed to it.
        *
        * Recursively increments the boolean array rather than converting to an int then converting back again.
        * Implemented in this manner for the same reasons we implemented increment_bool in its manner.
        */
       void add_to_bool(bool bool_to_add[REGISTER_BITS], unsigned int immediate);
        // the control unit has pointers to all these so it can access them directly
        DataMemory *ctrlDataMem = nullptr;
        Register *ctrlPC = nullptr;
        Register *ctrlRegisters[32];
        // the control unit doesn't need to access the instruction memory since it won't be messing with instructions, only with the program counter
        
        /*! \brief The function to call by which the control unit executes an instruction.
        *
        * Expected usage: processor hands the control unit an instruction via execute_instruction.
        * The control unit then handles setting the program counter for the next instruction
        * The control unit does not adjust the instruction memory; it is only handed one instruction at a time by the processor.
        * The control unit can affect the data memory, program counter, and all the other registers.
        */
        void execute_instruction(RiscvInstruction ctrlInstruction);

        ControlUnit();
        ~ControlUnit();
};

} // namespace riscv_emulator

#endif