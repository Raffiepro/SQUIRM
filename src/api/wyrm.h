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

  Data(int num) { this->num = num; }

  Data() {}
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

struct LexerInfo {
  std::string value;
  int end;
  bool valid;

  LexerInfo() {}

  LexerInfo(std::string value, int end, bool valid) {
    this->value = value;
    this->end = end;
    this->valid = valid;
  }

  LexerInfo(bool valid) { this->valid = valid; }
};

struct Literal { // Qualsevol cosa que no comenci amb un punt
  std::string name;
  LexerInfo (*policy)(char *, int); // El que retorna es el offset del literal,
                                    // el punter es a on detectar
  // Ha de retornar -1 en cas que no s'hagi detectat res

  Literal(std::string name, LexerInfo (*policy)(char *, int)) {
    this->name = name;
    this->policy = policy;
  }
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
  std::string elementType;

  union {
    void (*binaryOperation)(Data *a, Data *b, Data *res);
    void (*unaryOperation)(Data *a, Data *res);
    void (*conversion)(Data *res);
  };
};

class Library {
  std::string libraryName;
  std::string libraryDesc;

  std::vector<Type> types;
  std::vector<Operation> operations;
  std::vector<Literal> literals;

public:
  Library(std::string name, std::string description) {
    this->libraryName = name;
    this->libraryDesc = description;
  }

  std::string GetLibraryName() { return libraryName; }

  std::string GetLibraryDesc() { return libraryDesc; }

  std::vector<Type> GetTypeList() { return types; }

  std::vector<Operation> GetOperationList() { return operations; }

  std::vector<Literal> GetLiterals() { return literals; }

  void RegisterType(Type t) { types.push_back(t); }

  void RegisterOperation(Operation op) { operations.push_back(op); }

  void RegisterLiteral(Literal lit) { literals.push_back(lit); }

  int GetType(std::string typeName) {
    for (int i = 0; i < types.size(); i++) {
      if (types[i].name == typeName)
        return i;
    }
    return -1; // O throw
  }
};
} // namespace ThatAPI
