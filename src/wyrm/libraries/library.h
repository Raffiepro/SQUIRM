#pragma once

#include "../../api/wyrm.h"
#include <dlfcn.h>

#include <filesystem>
#include <vector>

namespace That {
    class Book {
        // std::vector<ThatAPI::Library> libs;
        public:
            std::vector<ThatAPI::Type> types;
            std::vector<ThatAPI::Operation> operations;
            std::vector<ThatAPI::Literal> literals;       

            Book();

            void RegisterLibraries();
            int GetTypeFromName(std::string name);
    };
}
