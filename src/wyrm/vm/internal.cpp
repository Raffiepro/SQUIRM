#include "internal.h"
#include "../headers/debug.hpp"

#include <iostream>
#include <map>
#include <tuple>
#include <unordered_map>

using namespace That;

void Internal::LoadOperations(
    Book *book, std::unordered_map<unsigned int, WyrmAPI::Operation> *ops) {
  for (int i = 0; i < book->operations.size(); i++) {
    ops->insert({i, book->operations[i]});
  }
}

unsigned int Internal::HashOperation(WyrmAPI::Operation op) {
  return op.operationType * (op.simbol * N_SYMBOLS + op.GetOperationId());
}

unsigned int Internal::HashOperation(WyrmAPI::OpType optype,
                                     WyrmAPI::OpSymbol symbol, int type) {
  return optype * (symbol * N_SYMBOLS + type);
}
