#ifndef RTYPEINSTRUCTION_H
#define RTYPEINSTRUCTION_H

#include "riscvInstruction.h"

namespace riscv_emulator {

/*! \brief R-Type instruction sub class. Includes rd, funct3, rs1, rs2, and funct7 as codes within the instruction.
*
*/
class RTypeInstruction: public RiscvInstruction {
    private:
        int rd;
        int funct3;
        int rs1;
        int rs2;
        int funct7;

        void set_rd();
        void set_funct3();
        void set_rs1();
        void set_rs2();
        void set_funct7();

    public:
        /*! \brief Overriden function for R-Type Instructions. Sets rd, funct3, rs1, rs2, and funct7 in addition to the opcode.
        *
        */
        void set_contents(bool updated_contents[32]);
        int get_rd() {return rd;}
        int get_funct3() {return funct3;}
        int get_rs1() {return rs1;}
        int get_rs2() {return rs2;}
        int get_funct7() {return funct7;}

};

} // namespace riscv_emulator

#endif