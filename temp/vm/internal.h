#pragma once

#include "../libraries/library.h"
#include "data.h"

#include <map>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace Wyrm {
namespace Internal {
enum InternalFunctions {
  PRINT,
  READ,
};

void LoadOperations(Book *book,
                    std::unordered_map<unsigned int, Operation> *ops);

unsigned int HashOperation(Operation op);
unsigned int HashOperation(WyrmAPI::OpType optype, WyrmAPI::OpSymbol symbol,
                           int type);
} // namespace Internal
} // namespace Wyrm
