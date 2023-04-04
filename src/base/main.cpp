#include <iostream>

#include "../api/that.h"

// Aqui posem algunes funcions
void IntegerAdd(ThatAPI::Data *a, ThatAPI::Data *b, ThatAPI::Data *res){
    std::cout << "Testeando" << std::endl;
}

extern "C" {
    ThatAPI::Library Load(){
        ThatAPI::Library l("base", "Base library of That");

        ThatAPI::Type integer;
        integer.cname = "int";
        integer.name = "int";
        integer.displayName = "Integer";
        integer.extended = false;
        integer.neutral = ThatAPI::Data(0);

        l.RegisterType(integer);

        ThatAPI::Operation integerAdd;
        
        integerAdd.operationType = ThatAPI::OpType::OP_BINARY;
        integerAdd.simbol = ThatAPI::OpSymbol::OP_ADD;
        integerAdd.elementType = l.GetType("Integer");
        integerAdd.binaryOperation = IntegerAdd;

        l.RegisterOperation(integerAdd);

        return l;
    }
}