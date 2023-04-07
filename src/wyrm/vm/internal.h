#pragma once

#include "data.h"
#include "../libraries/library.h"

#include <vector>
#include <map>
#include <unordered_map>
#include <tuple>

namespace That {
    namespace Internal {
        enum InternalFunctions {
            PRINT,
            READ,
        };
        
        void LoadOperations(Book *book, std::unordered_map<unsigned int, WyrmAPI::Operation> *ops);

        unsigned int HashOperation(WyrmAPI::Operation op);
        unsigned int HashOperation(WyrmAPI::OpType optype, WyrmAPI::OpSymbol symbol, int type);
    }
}