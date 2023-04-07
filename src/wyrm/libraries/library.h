#pragma once

#include "../../api/wyrm.h"
#include <dlfcn.h>

#include <filesystem>
#include <vector>

namespace That {
    class Book {
        // std::vector<WyrmAPI::Library> libs;
        public:
            std::vector<WyrmAPI::Type> types;
            std::vector<WyrmAPI::Operation> operations;
            std::vector<WyrmAPI::Literal> literals;       

            Book();

            void RegisterLibraries();
            int GetTypeFromName(std::string name);
    };
}
