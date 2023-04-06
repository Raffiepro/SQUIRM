#include <iostream>
#include <climits>

#include "machine.h"
#include "internal.h"
#include "../headers/debug.hpp"
#include "../flags/flags.h"
#include "../headers/termcolor.hpp"
#include "../libraries/library.h"

using namespace That;

void VM::MemDump(uint8_t *data, int size){
    std::cout << "[Dump] Size: " << size << std::endl;

    for(int i = 0; i < size; i++){
        std::cout << (int) *(data + i) << " ";
    }
    std::cout << std::endl;
    return;
}

VM::VM(Book *book, Flag::Flags flags){
    this->flags = flags;
    this->book = book;

    debug = CHECK_BIT(flags, 1);

    // Carreguem funcions internes
    Internal::LoadOperations(book, &operations);
}

void VM::Run(MachineCode code){
    // return;
    Atom* registers;
    registers = new Atom[code.regCount];
    offset = 0;

    for(int i = 0; i < code.instructions.size(); i++){
        try {
            Process(code.instructions[i], &i, &code.constants, registers);
        } catch(std::string r){
            Debug::LogError(r);
            break;
        }
    }

    if(debug) std::cout << "SIZE: " << code.regCount << std::endl;
    delete[] registers;
}

void VM::Process(Instruction ins, int* current, std::vector<Atom> *constants, Atom* registers){

    InstructionID tipus = ins.type;

    bool offseted = false;
    
    try {
        switch (tipus)
        {
        case InstructionID::LOADC: //A,B
            // if(debug) std::cout << "C: " << ins.GetB() << " (" << currentCode.constants[ins.GetB()].data.num << ") -> R: " << ins.GetA() << std::endl;
            registers[ins.GetA()] = (*constants)[ins.GetB()]; // TODO: Aixo copia ? Crec que no
            break;
        /* case InstructionID::DEF: // De momento es un print
            defaultFunctions[0](registers + ins.GetA(), 1);
            break; */
        case InstructionID::TEST:
            if(registers[ins.GetA()].data->num == 0){
                *current += ins.GetB() - 1;
            }
            break;
        case InstructionID::JUMP:
            *current += ins.GetA();
            break;
        case InstructionID::MOVE:
            registers[ins.GetB()] = registers[ins.GetA()];
            break;
        case InstructionID::CALL: // A: func, B --- C: params
            // A veure aqui caldria eh aconseguir la funció i constants de A i doncs executar recursivament i tal
            break;
        case InstructionID::BINARY:
            Operate((ThatAPI::OpSymbol) ins.GetA(), registers + ins.GetB(), registers + ins.GetC(), registers + ins.GetD());
            break;
        default: // Nose excepcion supongo??? XD
            throw(std::string("Undefined instruction error " + std::to_string(tipus)));
            break;
        }
        if(!offseted && offset != 0) offset = 0;
    } catch(std::string r){
        throw(r);
    }
    
    // if(debug) RegDump();
}

void VM::Operate(ThatAPI::OpSymbol op, Atom* a, Atom* b, Atom* c){
    //if(operations.count({op, a->type, b->type})){
    operations[Internal::HashOperation(ThatAPI::OpType::OP_BINARY, op, a->typeId)].binaryOperation(a->data, b->data, c->data);
    return;
    // TODO: Suport per operadors?
}

std::string VM::GetOperationName(ThatAPI::OpSymbol t){
    std::map<ThatAPI::OpSymbol, std::string> m = {
        {ThatAPI::OP_ADD,       "+"},
        {ThatAPI::OP_SUBTRACT,    "-"},
        {ThatAPI::OP_MUL,      "*"},
        {ThatAPI::OP_DIV,    "/"},
        {ThatAPI::OP_MOD,      "%"},
        {ThatAPI::OP_EQ,      "=="},
        {ThatAPI::OP_NEQ,      "!="},
        {ThatAPI::OP_NOT,      "!"},
        {ThatAPI::OP_GT,      ">"},
        {ThatAPI::OP_LT,      "<"},
        {ThatAPI::OP_GEQ,      ">="},
        {ThatAPI::OP_LEQ,      "<="},
        {ThatAPI::OP_AND,      "&&"},
        {ThatAPI::OP_OR,      "||"}
    };
    return m[t];
}