#include "include/processor.h"

namespace riscv_emulator {

void Processor::run_processor() {
    // we check the instruction memory's instruction at the address of the value in the program counter register
    // next, get check this particular instruction's contents
    // are the contents equal to zero? If so, halt. Else, hand the instruction to the control unit to execute.
    while (this->instrMem.get_instruction(this->pc.get_contents()).get_contents() != 0) {
        // execute the instruction at the address in instruction memory of the value contained in the program counter register
        this->processorCtrl.execute_instruction(this->instrMem.get_instruction(this->pc.get_contents()));
    }
}

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