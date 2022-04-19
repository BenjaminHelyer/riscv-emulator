#ifndef RISCVINSTRUCTION_H
#define RISCVINSTRUCTION_H

namespace riscv_emulator {

/*! \brief Base class for RISC-V instruction.
 *
 *
 * The RISC-V instruction class includes the basic tools needed to operate on an instruction.
 * The instruction contents should only be set as a whole, not by specific parts (e.g., should not just set the opcode).
 * The default value is for the entire contents of the instruction to be zero, since RISC-V has no instructions that are entirely zero.
 * Thus, encountering a zero instruction can be useful for programming.
 * Example: the processor can be made to halt or raise an error if it encounters a zero instruction.
 */
class RiscvInstruction {
    protected:
        bool contents[32] = { }; // RISC-V has no instructions that are entirely zero, which allows for quickly recognizing empty instructions
        int opcode; // make an integer opcode for easy readability, despite the contents being in binary
        char type;
        
        // don't want to be able to set the opcode or type unless the contents themselves are changed
        void set_opcode(); 
        void set_type();
    public:
        /*! \brief Sets the contents of the given instruction to a 32-bit binary array.
        *
        * The only way to update an instruction is to set all of its contents.
        * Setting only a part of the contents might lead to erroneous behavior and an invalid instruction.
        */
        void set_contents(bool updated_contents[32]);
        /*! \brief Gets the opcode of the given instruction as an integer.
        *
        * Returned as an integer for easy comparison purposes. Prevents iterating over an array each time.
        */
        int get_opcode() {return opcode; }
        /*! \brief Gets the type of the given instruction as a character.
        *
        * Returns the type so that the opcode doesn't have to be checked to determine the type each time.
        */
        int get_type() {return type; }
        RiscvInstruction();
};

} // namespace riscv_emulator

#endif