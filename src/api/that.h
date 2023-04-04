#pragma once
// That api handler

// Aquest header comunica entre el llenguatge i la api d'aquest

#include <string>
#include <vector>

#define N_SYMBOLS 14

namespace ThatAPI {

    struct Data {
        int num;
        uint8_t *data;

        Data(int num){
            this->num = num;
        }

        Data(){}
    };

    enum OpType {
        OP_UNARY,
        OP_BINARY,
        OP_CONVERSION,
    };

    enum OpSymbol {
        OP_ADD,
        OP_SUBTRACT,
        OP_MUL,
        OP_DIV,
        OP_MOD,
        OP_LT,
        OP_GT,
        OP_LEQ,
        OP_GEQ,
        OP_NEQ,
        OP_EQ,
        OP_AND,
        OP_OR,
        OP_NOT
    };

    enum LiteralPolicy {
        NULLABLE = 0,
        INTEGER = 1, // Genera .th, assembly del vm
        FLOAT = 1 << 1, // Cosa de debug
        BOOLEAN = 1 << 2,
        CHARACTER = 1 << 3, // Genera codi en C++ i compila un binari
        STRING = 1 << 4,
    };

    
    struct Type {
        std::string name;
        std::string cname;
        std::string displayName;
        bool extended;
        Data neutral;
    };


    struct Operation {
        OpSymbol simbol;
        OpType operationType;
        int elementType;

        union {
            void(*binaryOperation)(Data* a, Data* b, Data* res);
            void(*unaryOperation)(Data* a, Data* res);
            void(*conversion)(Data* res);
        };
    };

    class Library {
        std::string libraryName;
        std::string libraryDesc;

        std::vector<Type> types;
        std::vector<Operation> operations;

        public:
            Library(std::string name, std::string description){
                this->libraryName = name;
                this->libraryDesc = description;
            }

            std::string GetLibraryName(){
                return libraryName;
            }

            std::vector<Type> GetTypeList(){
                return types;
            }

            std::vector<Operation> GetOperationList(){
                return operations;
            }

            void RegisterType(Type t){
                types.push_back(t);
            }

            void RegisterOperation(Operation op){
                operations.push_back(op);
            }

            int GetType(std::string typeName){
                for(int i = 0; i < types.size(); i++){
                    if(types[i].name == typeName) return i;
                }
                return -1; // O throw
            }
    };
}
