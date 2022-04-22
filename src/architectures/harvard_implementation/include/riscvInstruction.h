#ifndef RISCVINSTRUCTION_H
#define RISCVINSTRUCTION_H

namespace riscv_emulator {

// global constant for instruction length is not defined since changing the instruction length would change the essence of the ISA

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
        
        // don't want to be able to set the opcode or type unless the contents themselves are changed
        void set_opcode(); 
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
        /*! \brief Gets the contents of the instruction and returns it as an unsigned long.
        *
        */
        unsigned long get_contents();
        /*! \brief Copies the contents of the instruction into an array.
        *
        * This is instead of returning the pointer to the private contents array.
        */
        void copy_contents(bool input_array[32]);
        /*! \brief Copies the non-opcode fields of the instruction into an array.
        *
        * This may not be used much or at all by the processor, but it's nice to have and minimally difficult to use.
        */
       void copy_nonopcode_fields(bool input_array[25]);
       /*! \brief Gets a set of bits from the instruction and copies them into a given array. Usage: input_array should be of length (last_bit - first_bit + 1). This function is inclusive with respect to the last_bit index.
       *
       * Meant to serve as an interface between the RiscvInstruction class and the ControlUnit class,
       * in that it provides a set of bits of a RiscvInstruction without pre-determining what they are supposed to be used for.
       * Other specific functions at the ControlUnit level then can call this function for specific uses of these bits.
       * 
       * Usage example: get_bits(3, 7, my_array[5]) results in my_array containing the following after the instruction: [bit_3, bit_4, bit_5, bit_6, bit_7]
       */
       void get_bits(int first_bit, int last_bit, bool input_array[]);

       RiscvInstruction();
};

} // namespace riscv_emulator

#endif