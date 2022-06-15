#include "include/commands.h"
#include "../../architectures/harvard_implementation/include/riscvInstruction.h"
#include "../../architectures/harvard_implementation/include/dataMemory.h"
#include "../../architectures/harvard_implementation/include/processor.h"
#include "../../architectures/harvard_implementation/include/register.h"
#include "../../architectures/harvard_implementation/include/instructionMemory.h"
#include "../../architectures/harvard_implementation/include/controlUnit.h"
#include "../../architectures/harvard_implementation/include/processor.h"
#include "../../architectures/harvard_implementation/include/ioPeripheral.h"

#include <iostream>
#include <string>

namespace riscv_emulator {

void Commands::run_interface() {
    while (!(this->stop_process)) {
        std::cout << "Please enter a command. Enter 'HELP' for help." << std::endl;
        std::string usr_command = "";
        std::cin >> usr_command;
        this->process_user_command(usr_command);
    }

    // return when stop_process is pulled high
    return;
}

void Commands::process_user_command(std::string in_command) {
    if (in_command == "HELP") {
        this->print_command_list();
    }
    else if (in_command == "STOP") {
        this->stop_emu();
        this->stop_process = 1;
        std::cout << "Emulator stopped. Stopping command interface..." << std::endl;
    }
    // TODO: cover the edge case where a user *only* enters the first segment of words for a valid command, currently just waits for more input without giving an error prompt
    // could have it print out a statement like "What would you like to print?" to cover this case
    else if (in_command == "PRINT") {
        // grab the second word from the string following a print command
        std::string second_word = "";
        std::cin >> second_word;
        if (second_word == "REG") {
            std::string third_word = "";
            std::cin >> third_word;
            if (third_word == "*") {
                this->print_all_regs();
            }
            else {
                std::cout << "Command not recognized. Please try again or enter 'HELP' for help (without the quotation marks)." << std::endl;
            }
        }
        else {
            std::cout << "Command not recognized. Please try again or enter 'HELP' for help (without the quotation marks)." << std::endl;
        }
    }
    else {
        std::cout << "Command not recognized. Please try again or enter 'HELP' for help (without the quotation marks)." << std::endl;
    }

    return;
}

void Commands::print_command_list() {
    std::cout << "List of commands:" << std::endl;
    std::cout << "STOP -- Stops the emulator and prints out a confirmation message once stopped." << std::endl;
    std::cout << "HELP -- Prints out a list of commands." << std::endl;
    std::cout << "PRINT REG * -- Prints out the contents of all the registers." << std::endl;

    return;
}

void Commands::stop_emu() {
    // plaeholder for now, implemented this is a function in case a more complex destructor is needed for stopping the emulator
    std::cout << "Stopping emulator..." << std::endl;

    return;
}

void Commands::print_register_contents(Register reg) {
    bool reg_contents[32] = { };
    reg.copy_contents(reg_contents);
    for (int i = 0; i < REGISTER_BITS; i++) {
        std::cout << reg_contents[i];
    }
}

void Commands::print_all_regs() {
    std::cout << "Here are the contents of all the registers:" << std::endl;

    for (int i = 0; i < 32; i++) {
        std::cout << "Contents of register X" << i << ": ";
        print_register_contents(this->emuProcessor.registers[i]);
        std::cout << std::endl;
    }

    return;
}

Commands::Commands() {
    // add in default constructor later if needed
}

} // namespace riscv_emulator
