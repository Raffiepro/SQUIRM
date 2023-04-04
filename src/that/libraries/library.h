#pragma once

#include "../../api/that.h"
#include <dlfcn.h>

#include <filesystem>
#include <vector>

namespace That {
    class Book {
        // std::vector<ThatAPI::Library> libs;
        public:
            std::vector<ThatAPI::Type> types;
            std::vector<ThatAPI::Operation> operations;
            
            Book();

            void RegisterLibraries();
            int GetTypeFromName(std::string name);
    };
}