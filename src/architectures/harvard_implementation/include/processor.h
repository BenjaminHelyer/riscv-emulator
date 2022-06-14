#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "instructionMemory.h"
#include "register.h"
#include "riscvInstruction.h"
#include "dataMemory.h"
#include "controlUnit.h"
#include "ioPeripheral.h"

#include <string>

namespace riscv_emulator {

/*! \brief The essense of the emulator. The processor is the basic unit which this project strives to mimic.
*
*/
class Processor {
    // strictly speaking, a struct should probably be used here since everything is public, but classes have been used for everything else, so we'll stick with a class
    public:
        ControlUnit processorCtrl;
        InstructionMemory instrMem;
        DataMemory dataMem;
        Register pc;
        // TODO: find a way to hold the zero register value as a hardwired zero. Simple solution would be to drive the contents to zero at the beginning and end of each processor cycle.
        Register registers[32]; // holds all registers other than the pc, including the zero register
        IoPeripheral processor_io;

        /*! \brief Fundamental function to run the processor. Starts reading instructions in memory from address 0 onwards.
        *
        */
        void run_processor();
        /*! \brief Loads instructions into the processor's instruction memory from file. Currently, instructions must be in strings of machine code, one instruction per line, with no skipped lines.
        *
        */
        void load_instructions_from_file(std::string filename);

        Processor();
};

} // namespace riscv_emulator

#endif