#pragma once

#include <vector>
#include <string>

#include "assembler.h"

namespace Wyrm {
    class Serializer {
        public:
            Serializer(Book *book);

            void Serialize(MachineCode assembly);
            void SerializeToFile(std::string fileName, MachineCode assembly);
            void SerializeFromFile(std::string fileName, MachineCode *code);
        private:
            void WriteConst(FILE* f, Atom reg);
            void WriteInstruction(FILE *f, Instruction ins);
            void ReadConst(FILE *f, std::vector<Atom> *constants);
            bool ReadInstruction(FILE *f, std::vector<Instruction> *instructions);

            Book *book;
    };
}