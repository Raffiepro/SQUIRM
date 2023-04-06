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
        
        void LoadOperations(Book *book, std::unordered_map<unsigned int, ThatAPI::Operation> *ops);

        unsigned int HashOperation(ThatAPI::Operation op);
        unsigned int HashOperation(ThatAPI::OpType optype, ThatAPI::OpSymbol symbol, int type);
    }
}