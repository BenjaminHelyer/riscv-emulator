#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include "dataMemory.h"
#include "instructionMemory.h"
#include "register.h"
#include "riscvInstruction.h"

namespace riscv_emulator {

/*! \brief Class for the control unit, which is the decision-making heart of the processor.
*
* This class includes peripherals as pointers rather than members.
* Rationale: the types of peripherals should be able to be adjusted as part of the overall processor
* without affecting the control unit.
*
* Functions that depend on the type of instruction are implemented here rather than in the RiscvInstruction class.
* Rationale: Instruction type is determined at the level of the control unit rather than at the level of the instruction itself.
* Thus, defining functions for all instructions which are only valid for specific instruction types might lead to confusing
* or outright incorrect results.
*/
class ControlUnit {
    private:
        /*! \brief Gets the extended opcode for a boolean array representing an instruction.
        *
        * Not implemented in RiscvInstruction class since not all instructions have an extended opcode.
        * Once the processor sees that this instruction is of a type with an extended opcode, it gets the extended opcode.
        * Similar to other functions, the basis for the interface between this function and the RiscvInstruction object is the copy_bits function.
        */
        int get_opcode_extend(RiscvInstruction instr);
        /*! \brief Gets the destination register for the instructions for which this applies. Returns as an int.
        *
        * Destination register lies in bits 7 through 11 in all instructions for which it applies.
        * Returns destination register value as an int. Rationale: This value can be later used for indexing the array of registers.
        */
        int get_rd(RiscvInstruction instr);
        /*! \brief Gets the source register rs1 for the instructions for which this applies. Returns as an int.
        *
        * Destination register lies in bits 15 through 19 in all instructions for which it applies.
        * Returns destination register value as an int. Rationale: This value can be later used for indexing the array of registers.
        */
        int get_rs1(RiscvInstruction instr);


        // Begin functions for overall instructions.
        /*! \brief U lui: Loads a 20-bit immediate into the 20 most-significant-bits of the destination register.
        *
        * Combined with one other 12-bit immediate instruction, the a full 32-bit immediate can be loaded into a register.
        * Example: U lui followed by I addi has this result
        */
        void u_lui(RiscvInstruction instr);
        /*! \brief I addi: adds a 12-bit immediate from a source register to a destination register. The immediate is added to the 12 least significant bits.
        *
        */
        void i_addi(RiscvInstruction instr);

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