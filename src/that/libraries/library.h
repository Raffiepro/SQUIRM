#pragma once

#include "../that.h"
#include <dlfcn.h>

#include <filesystem>
#include <vector>

namespace That {
    class Book {
        std::vector<ThatAPI::Library> libs;

        public:
            Book();
    };
}