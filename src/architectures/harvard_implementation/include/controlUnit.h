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
        /*! \brief Gets the source register rs2 for the instructions for which this applies. Returns as an int.
        *
        * Destination register lies in bits 15 through 19 in all instructions for which it applies.
        * Returns destination register value as an int. Rationale: This value can be later used for indexing the array of registers.
        */
        int get_rs2(RiscvInstruction instr);
        /*! \brief Gets an unsigned int representing the 12-bit immediate value in I-type instructions. This value is sign-extended to a 32-bit signed integer.
        *
        * Since the value is sign-extended, be careful: a value over 2^31 - 1 means the number is negative and will be operated with as such.
        */
        unsigned int get_upper_12_immediate(RiscvInstruction instr);
        /*! \brief Gets the PC-relative address as an integer for B-type instructions. This does NOT work for J instructions, since the address immediate is stored differently in those instructions.
        *
        * B-type instructions store the address immediate into a lower 5 bits and an upper 7 bits separated by rs1 and rs2 in the instruction.
        * This is because B-type instructions use the rs2 space, so there isn't room for a full 12-bit immediate on the upper side of the instruction.
        * 
        * The process for getting the address is multiplying the 12-bit immediate by 2 and afterwards sign-extending it.
        * 
        * This function does not increment the PC. That is done in the functions for the B-type instructions themselves.
        */
        unsigned int get_address_b_type(RiscvInstruction instr); 
        /*! \brief Sign-extends a 32-bit boolean array with a value in its lowest 12 bits. ("upper_12" name comes from the fact that these are the upper 12 bits int he instruction)
        *
        */
        void sign_extend_12_bit(bool bool_with_12_bit_val[32]);

        // Begin functions for overall instructions.
        /*! \brief U lui: Loads a 20-bit immediate into the 20 most-significant-bits of the destination register.
        *
        * Combined with one other 12-bit immediate instruction, the a full 32-bit immediate can be loaded into a register.
        * Example: U lui followed by I addi has this result
        */
        void u_lui(RiscvInstruction instr);
        /*! \brief I addi: adds a 12-bit immediate from a source register to a destination register. The immediate is added to the 12 least significant bits.
        *
        * As with all arithmetic instructions, the immediate is sign-extended to a 32-bit signed immediate value.
        */
        void i_addi(RiscvInstruction instr);
        /*! \brief I andi: logical AND operation with a 12-bit immediate (sign-extended to a 32-bit signed immediate) acting on a source register, saving the result in a destination register.
        *
        */
        void i_andi(RiscvInstruction instr);
        /*! \brief I ori: logical OR operation with a 12-bit immediate.
        *
        */
        void i_ori(RiscvInstruction instr);
        /*! \brief I xori: logical XOR operation with a 12-bit immediate.
        *
        */
        void i_xori(RiscvInstruction instr);
        /*! \brief I slti: "set less than immediate," sets the destination register to 1 if rs1 is less than the signed immediate value.
        *
        */
        void i_slti(RiscvInstruction instr);
        /*! \brief I sltiu: "set less than immediate unsigned," sets the destination register to 1 if rs1 is less than the unsigned immediate value.
        *
        */
        void i_sltiu(RiscvInstruction instr);
        /*! \brief B beq: "branch if equal," branches to another instruction if the two operand registers are equal.
        *
        * Since we chose to simply increment the PC by units of 1 rather than units of 4 (since we are using an array for instructions,
        * which already has multiple words per index), in this emulation, the 12-bit immediate used for the address is simply sign-extended
        * then added to the PC. This may be adjusted in future updates if a more realistic model of RISC-V is needed.
        * 
        * In reality, the 12-bit immediate would be multiplied by 2, sign-extended, and after all that, finally added to the PC.
        * The reason for this is that RISC-V instructions are multiples of two bytes long.
        */
        void b_beq(RiscvInstruction instr);
        /*! \brief B bne: "branch if not equal," branches to another instruction if the two operand registers are equal.
        *
        * The same qualifications as in B beq apply to this instruction.
        */
        void b_bne(RiscvInstruction instr);
        /*! \brief B bne: "branch if less than," branches to another instruction if the first operand is less than the second.
        *
        * The same qualifications as in B beq apply to this instruction.
        */
        void b_blt(RiscvInstruction instr);
        /*! \brief B bge: "branch if greater than or equal to," branches to another instruction if the first operand is greater than or equal to the second.
        *
        * The same qualifications as in B beq apply to this instruction.
        */
        void b_bge(RiscvInstruction instr); 

    public:
        /*! \brief Increments the PC by copying the contents of the PC then incrementing the resulting boolean array.
        *
        */
        void increment_pc();
        /*! \brief Decrements the PC by copying the contents of the PC then incrementing the resulting boolean array.
        *
        */
        void decrement_pc();
        /*! \brief Adjusts the PC based on a given PC-relative address.
        *
        */
        void adjust_PC_with_address(unsigned int address);
        /*! \brief Function for incrementing a boolean array. Note that this function alters the array that is passed to it.
        *
        * Sign-extended incrementation for a boolean array. Thus, a bool which is the max. positive value will be "incremented" to the max. negative value.
        * All other incrementations are positive addition except for this sign flip.
        *
        * Implemented addition in this way because the average runtime for incrementing an array in this way is better than converting a boolean array to an int then converting the int back into an array.
        * In fact, for converting a boolean array to an int, the runtime would consistently be the length of the array.
        * Thus, the runtime for converting an array to an int and back again would be twice the worst-case runtime for addition in this method.
        */
        void increment_bool(bool bool_to_increment[REGISTER_BITS]);
        /*! \brief Function for decrementing a boolean array. Note that this function alters the array that is passed to it.
        *
        */
        void decrement_bool(bool bool_to_decrement[REGISTER_BITS]);
        /*! \brief Function for adding an immediate value to a boolean array. Note that this function alters the array that is passed to it.
        *
        * Based on the sign-extended incrementation function, this function also works in a sign-extended manner,
        * assuming that the immediate passed to it is unsigned. Thus, an int value over 2^31 - 1 will act as a negative
        * value for this function, adding a negative value instead of a positive value.
        * This behavior makes this function consistent with RISC-V's sign-extended behavior.
        * 
        * Recursively increments the boolean array rather than converting to an int then converting back again.
        * Implemented in this manner for the same reasons we implemented increment_bool in its manner.
        */
       void add_to_bool(bool bool_to_add[REGISTER_BITS], unsigned int immediate);
       /*! \brief Function for comparing two boolean arrays which returns -1 if the first argument is greater, 1 if the second argument is greater, and 0 if the bools are equal.
       *
       * This abstraction is useful for representing any comparison operation, which will allow us to have just one C++ function
       * for comparing values even when there are multiple RISC-V functions for this. Rationale: ease of implmenetation on the
       * C++ side. This may be changed later if a more accurate abstraction is desired.
       * 
       * The comparison is implemented by beginning at the end of each bool rather than the beginning. This allows quick
       * determination for numbers that differ in sign. For this reason it seems that on average this implementation has
       * a faster runtime than starting at the beginning. The worst-case runtime is still the same for both.
       */
       int compare_two_bools_signed(bool bool0[REGISTER_BITS], bool bool1[REGISTER_BITS]);
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