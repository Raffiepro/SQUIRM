#pragma once

#include "../_base.h"
#include "../kernel/library.h"

#include <vector>
#include <string>

namespace Wyrm {
    class Serializer {
        public:
            Serializer(Book *book);
            void Serializer::SerializeToFile(WyrmAPI::TreeCode assembly, std::string fileName);

            void SerializeString(FILE *f, std::string s);
            void SerializeAtom(FILE *f, WyrmAPI::Atom* atom);
            void SerializeNode(FILE* f, WyrmAPI::Node *n, std::vector<std::string>& libs);
        private:
            Book *book;
    };
}