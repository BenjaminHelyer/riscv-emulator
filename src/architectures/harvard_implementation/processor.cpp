#include "include/processor.h"

namespace riscv_emulator {

Processor::Processor() {
    // data memory, instruction memory, and registers were already all set to zero in their default constructors
    // set the correct pointers for the processor's control unit
    this->processorCtrl.ctrlDataMem = &this->dataMem;
    this->processorCtrl.ctrlPC = &this->pc;
    // go through all the control unit's register pointers, pointing them to the correct registers in the processor
    for (int i = 0; i < 32; i++) {
        this->processorCtrl.ctrlRegisters[i] = &this->registers[i];
    }
}

} // namespace riscv_emulator