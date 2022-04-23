#ifndef IOPERIPHERAL_H
#define IOPERIPHERAL_H

#include "dataMemory.h"
#include "instructionMemory.h"

#include <string>
#include <fstream>

namespace riscv_emulator {

/*! \brief Class for ioPerhipheral(s). This can be attached to the processor to represent streaming instructions and data to the relevent memories.
*
* Currently, this class writes directly to a given instruction memory or a given data memory.
* Rationale: Straightforward solution right now to expedite testing of the overall system.
*
* Once further use cases are determined, the class can be further refined to include better abstraction.
*/
class IoPeripheral {
    private:
        std::ifstream instr_stream;
        std::ifstream data_stream;
    public:
        void write_instr_to_mem(std::string filename, InstructionMemory &instr_mem);
        void write_data_to_mem(std::string filename, DataMemory &data_mem);
};

} // namespace riscv_emulator

#endif

