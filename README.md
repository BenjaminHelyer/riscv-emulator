# riscv-emulator
Emulator which aims to include functionality for RV32I, the base ISA of RISC-V.
The emulator can currently run about 40% of RISC-V instructions written in machine code in a text file.
This allows basic examples to be run to demonstrate the functionality of the emulator.

Currently, the emulator can be interacted with via a command line interface obtained by running an executable.
More functionaltiy will of course be added. The immediate goal is to get 100% of RISC-V instructions to be readable
by the emulator.

## Running Machine Code with the Emulator
For the first example, make the source code, run the resulting executable ("mymake.exe"), and follow the instructions here.
Once the executable is running, type the following, hitting enter after each line:

PRINT REG *

RUN examples/addi_sll.txt

PRINT REG *

Now, what did we just do? "PRINT REG *" tells the emulator to show us the contents of all the registers, which hold
the important values for operations being done by the processor. We use this command before and after running our
example file holding machine code, which is accomplished by the "RUN (filepath)" command.

Opening up the "addi_sll.txt" file reveals the machine code, with each instruction delimited by newlines.
For more details on how to translate this into assembly, see the **Resources** section. To spare the sweat
of translating this particular example, the assembly is given as follows:

ADDI X1, X1, 3

ADDI X2, X2, 1

SLL X3, X1, X2

This adds 3 to register X1, adds 1 to register X2, then sets X3 to be the contents of X1, logically shifted left a number
of times equal to the contents of X2. In this case, this sets X3 to be the contents of X1, logically shifted left by 1 bit (since X2 holds a value of 1). This hinges on the assumption that X1 and X2 are initially zero, which is the case upon a fresh startup
of the processor.

## Resources:
Below are a list of resources I've found to be helful when developing this project.
The resources are listed in order of most accessible to least accessible for someone with no previous background. In this case, this
also means that the list is sorted in roughly reverse order of relevence and brevity.

*Modern Computer Architecture and Organization* by Ledin. I recommend this to those who want a broad, rather than deep, overview of topics surrounding computer architecture and embedded systems. It contains great exercises and explanations and is written in such a way to not take too much of a busy professional's or self-learner's time. (Given an review copy of this book by Packt, so a big thank you to them for providing such an excellent reference!)

*The RISC-V Reader: An Open Architecture Atlas* by Patterson & Waterman.

*The RISC-V Instruction Set Manual* by Waterman & Asanovic. 


