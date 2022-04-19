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
    private:
        /*! \brief Pointer to a sub-class of the RiscvInstruction class. This pointer is used to retrieve members depending on the type of instruction.
        *
        * This is used rather than making every instruction an instruction of a particular type so that we can make an array of instructions in the memory.
        * The array of instructions in memory then simply has instructions of the base-class, with functions operating on the base class that yield the values from the typed classes.
        */
       RiscvInstruction *typedInstruction;

        /*! \brief Sets the pointer typedInstruction based on the current type of the RiscvInstruction.
        *
        */
       void set_pointer_from_type(char currType);

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
        /*! \brief Virtual function for getting the rd value. If try to run this function on the base class, it will return -1.
        *
        */
        virtual int get_rd() {return -1;}
        /*! \brief Virtual function for getting the funct3 value. If try to run this function on the base class, it will return -1.
        *
        */
        virtual int get_funct3() {return -1;}
        /*! \brief Virtual function for getting the rs1 value. If try to run this function on the base class, it will return -1.
        *
        */
        virtual int get_rs1() {return -1;}
        /*! \brief Virtual function for getting the rs2 value. If try to run this function on the base class, it will return -1.
        *
        */
        virtual int get_rs2() {return -1;}
        /*! \brief Virtual function for getting the funct7 value. If try to run this function on the base class, it will return -1.
        *
        */
        virtual int get_funct7() {return -1;}

        RiscvInstruction();
        ~RiscvInstruction();
};

} // namespace riscv_emulator

#endif