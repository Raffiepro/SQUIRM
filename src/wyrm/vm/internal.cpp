#include "internal.h"
#include "../headers/debug.hpp"

#include <iostream>
#include <map>
#include <unordered_map>
#include <tuple>

using namespace That;

void Internal::LoadOperations(Book *book, std::unordered_map<unsigned int, ThatAPI::Operation> *ops){
    for(int i = 0; i < book->operations.size(); i++){  
        ops->insert({i, book->operations[i]});
    }
}

unsigned int Internal::HashOperation(ThatAPI::Operation op){
    return op.operationType * (op.simbol * N_SYMBOLS + op.elementType);
}

unsigned int Internal::HashOperation(ThatAPI::OpType optype, ThatAPI::OpSymbol symbol, int type){
    return optype * (symbol * N_SYMBOLS + type);
}