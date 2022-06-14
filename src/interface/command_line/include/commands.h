#ifndef COMMANDS_H
#define COMMANDS_H

#include "../../../architectures/harvard_implementation/include/processor.h"
#include "../../../architectures/harvard_implementation/include/register.h"

#include <iostream>
#include <string>

namespace riscv_emulator {

/*! \brief Basic class for the command line interface, holding the necessary objects and functions for running an interface.
*
*/
class Commands {
    private:
        Processor emuProcessor;
        bool stop_process = 0;
        /*! \brief Loads machine code from a text file. Instructions should be delimited by newlines, and only one instruction is allowed per line.
        *
        * Upon hitting a zero instruction, the processor will stop the task from this file.
        */
        void load_machine_code_from_txt_file(std::string filename);
        /*! \brief Displays the register contents to the command line for a given register.
        *
        */
        void display_register_contents(Register reg);

    public:
        /*! \brief Function for running the commnand-line interface. Called to generate a user-interactive interface in the command line.
        *
        * Example usage: In main(), simply call "run_interface();", this will enter into a loop of running the interface. 
        */
        void run_interface();
        /*! \brief Function to stop the interface. Generally doesn't need to be used, since this is implemented internally in run_interface().
        *
        */
        void stop_interface();

        Commands();
};

} // namespace riscv_emulator

#endif