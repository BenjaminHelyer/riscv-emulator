#ifndef REGISTER_H
#define REGISTER_H

namespace riscv_emulator {

const int REGISTER_BITS = 32;

/*! \brief Simple class for registers.  For now, will handle distinctions at the processor level.
*
* Alternatives for future improvement include defining distinct classes for x0 and PC.
* This would add complexity, however, and right now it's not clear what it would add to the system.
*/
class Register {
    private:
        bool contents[REGISTER_BITS] = { };
    public:
        /*! \brief Sets the contents of a register via a boolean array. For RV32I, the array length will be 32, but for other implementations this may change.
        *
        */
        void set_contents(bool updated_contents[REGISTER_BITS]);
        /*! \brief Gets the contents of a register and returns them as an unsigned long, since register values are normally > 16 bits.
        *
        */
        unsigned long get_contents();
        /*! \brief Copies the contents of a register into a given array.
        *
        */
        void copy_contents(bool given_array[REGISTER_BITS]);

        Register();
}; 

} // riscv_emulator

#endif