#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include <unordered_map>
#include <stack>

#include "internal.h"
#include "data.h"
#include "../flags/flags.h"
#include "../libraries/library.h"

#define UINT32_SIZE 4

namespace That {
    class VM {
        
        public:
            VM(Book *book, Flag::Flags flags);
            void Run(MachineCode code);
            
        private:
            // std::vector<reg_t> stack;
            Flag::Flags flags;
            Book *book;

            // std::stack<int> offsets;
            std::unordered_map<unsigned int, ThatAPI::Operation> operations;

            void MemDump(uint8_t *data, int size);

            void Process(Instruction ins, int* current, std::vector<Atom> *constants, Atom* registers);
            void Operate(ThatAPI::OpSymbol op, Atom* a, Atom* b, Atom *c);

            std::string GetOperationName(ThatAPI::OpSymbol t);

            bool debug;
            unsigned int offset;
            
            // void RegDump(Regs* regs, int n);
    };
}