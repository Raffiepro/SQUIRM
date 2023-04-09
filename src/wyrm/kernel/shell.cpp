#include "shell.h"
#include "kernel.h"

#include <iostream>
#include "../headers/termcolor.hpp"
#include "../flags/flags.h"

Wyrm::Shell::Shell(){

}

Wyrm::Shell::~Shell(){

}

void Wyrm::Shell::CreateShell(Kernel *kernel){
    std::string line;

    std::cout << termcolor::color<255, 168, 46> << termcolor::bold << ">> " << termcolor::reset;

    while(getline(std::cin, line)){

        // kernel->Compile(line, Flag::Flags::RUN);

        std::cout << termcolor::color<255, 168, 46> << termcolor::bold << ">> " << termcolor::reset;
    }
}