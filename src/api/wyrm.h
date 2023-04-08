#pragma once
// That api handler

// Aquest header comunica entre el llenguatge i la api d'aquest

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#define N_SYMBOLS 14

namespace WyrmAPI {

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
  OP_NOT,
  OP_AMP,
  OP_PIPE,
  OP_QM,
  OP_IQM,
  OP_UP,
  OP_AT,
  OP_LEFTSHIFT,
  OP_RIGHTSHIFT,
  OP_MEQ,
  OP_MNEQ,
  OP_DOLLAR,
  OP_ARROW_RIGHT,
  OP_ARROW_LEFT
};

enum TokenType {
  ADD,               // +
  SUBTRACT,          // -
  MULTIPLY,          // *
  DIVIDE,            // /
  MODULO,            // %
  AMPERSAND,         // &
  PIPE,              // |
  QUESTION_MARK,     // ?
  INV_QUESTION_MARK, // ¿
  UP_ARROW,          // ^
  AT_SYMBOL,         // @
  LEFT_SHIFT,        // <<
  RIGHT_SHIFT,       // >>

  AND, // &&
  OR,  // ||
  NOT, // !

  EQUAL, // ==
  MORE_EQUAL,
  NOT_EQUAL,
  NOT_MORE_EQUAL,     // !=
  GREATER_THAN,       // >
  LESSER_THAN,        // <
  GREATER_EQUAL_THAN, // >=
  LESSER_EQUAL_THAN,  // <=

  INCREMENT, // ++
  DECREMENT, // --

  ASSIGMENT,          // =
  ASSIGMENT_ADD,      // +=
  ASSIGMENT_SUBTRACT, // -=
  ASSIGMENT_MULTIPLY, // *=
  ASSIGMENT_DIVIDE,   // /=
  ASSIGMENT_MODULO,   // %=

  COMMA,                // ,
  POINT,                // .
  PARENTHESIS_OPEN,     // (
  PARENTHESIS_CLOSE,    // )
  SQUARE_BRACKET_OPEN,  // [
  SQUARE_BRACKET_CLOSE, // ]
  CURLY_BRACKET_OPEN,   // {
  CURLY_BRACKET_CLOSE,  // }
  DOLLAR,               // $
  SEMICOLON,            // ;

  TWO_POINTS, // :
  ARROW_RIGHT,
  ARROW_LEFT,
  LONG_ARROW_RIGHT,
  LONG_ARROW_LEFT,
  WIDE_ARROW_RIGHT,
  WIDE_ARROW_LEFT,
  LONG_WIDE_ARROW_RIGHT,
  LONG_WIDE_ARROW_LEFT, // ->
  QUOT,                 // '
  DOUBLE_QUOT,          // "

  IF,       // if
  ELSE,     // else
  WHILE,    // while
  FOR,      // for
  RETURN,   // return
  BREAK,    // stop
  CONTINUE, // skip

  LITERAL, // 3
  TYPE,    // int

  FUNCTION_DECLARATION, // func
  MODULE_DECLARATION,   // use
  IMPORT_DECLARATION,   // import

  IDENTIFIER, // algo
  SEPARATOR,

  ERROR
};

struct LexerInfo {
  std::string value;
  bool valid;
  int end;

  LexerInfo() {}

  LexerInfo(bool valid, std::string value, int end) {
    this->value = value;
    this->valid = valid;
    this->end = end;
  }

  LexerInfo(bool valid) { this->valid = valid; }
};

struct Literal { // Qualsevol cosa que no comenci amb un punt
  std::string name;
  LexerInfo *(*policy)(char *); // El que retorna es el offset del literal,
                                // el punter es a on detectar
  // Ha de retornar -1 en cas que no s'hagi detectat res

  Literal(std::string name, LexerInfo *(*policy)(char *)) {
    this->name = name;
    this->policy = policy;
  }
};

struct Type {
  std::string wname;
  std::string cname;
  std::string name;
  bool extended;
  Data neutral;
};

class Operation {
public:
  OpSymbol simbol;
  OpType operationType;
  std::string elementType;

  int GetOperationId() { return elementTypeId; }

  void SetOperationId(int id) { elementTypeId = id; }

  union {
    void (*binaryOperation)(Data *a, Data *b, Data *res);
    void (*unaryOperation)(Data *a, Data *res);
    void (*conversion)(Data *res);
  };

private:
  int elementTypeId;
};

struct LoadInfo {
  std::string name;
  std::string desc;
};

class Library {
public:
  virtual LoadInfo PreLoad() { return LoadInfo(); }
  virtual void Load(){};

  void RegisterType(Type *t) { types.push_back(t); }

  void RegisterOperation(OpSymbol symbol, OpType opType,
                         std::string elementType, std::string opFunction) {
    opPreloadData.push_back({symbol, opType, elementType, opFunction});
  }

  void RegisterLiteral(std::string name, std::string policyFunc) {
    litPreloadData.push_back({name, policyFunc});
  }

  std::vector<Type *> _GetTypeList() { return types; }

  std::vector<std::tuple<OpSymbol, OpType, std::string, std::string>>
  _GetOperations() {
    return opPreloadData;
  }
  std::vector<std::tuple<std::string, std::string>> _GetLiterals() {
    return litPreloadData;
  }

private:
  std::vector<Type *> types;
  std::vector<Operation> operations;
  std::vector<Literal> literals;

  std::vector<std::tuple<OpSymbol, OpType, std::string, std::string>>
      opPreloadData;
  std::vector<std::tuple<std::string, std::string>> litPreloadData;
};
/*
class Library {
  std::string libraryName;
  std::string libraryDesc;

  std::vector<Type> types;
  std::vector<Operation> operations;
  std::vector<Literal> literals;

public:
  Library() {}

  Library(std::string name, std::string description) {
    this->libraryName = name;
    this->libraryDesc = description;
  }

  virtual void Load();

  std::string GetLibraryName() { return libraryName; }

  std::string GetLibraryDesc() { return libraryDesc; }

  std::vector<Type> GetTypeList() { return types; }

  std::vector<Operation> GetOperationList() { return operations; }

  std::vector<Literal> GetLiterals() { return literals; }

  void RegisterType(Type t) { types.push_back(t); }

  void RegisterOperation(Operation op) { operations.push_back(op); }

  void RegisterLiteral(Literal lit) {
    literals.push_back(lit);
    std::cout << "Literal registrado" << std::endl;
  }

  int GetType(std::string typeName) {
    for (int i = 0; i < types.size(); i++) {
      if (types[i].name == typeName)
        return i;
    }
    return -1; // O throw
  }
};
  */
} // namespace WyrmAPI
