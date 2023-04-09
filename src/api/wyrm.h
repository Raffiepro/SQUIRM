#pragma once
// Wyrm api handler

// Aquest header comunica entre el llenguatge i la api d'aquest

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#define N_SYMBOLS 27

namespace WyrmAPI {

struct Data {
  int num;
  void *data;

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

struct LoadInfo {
  std::string name;
  std::string desc;
};

class Library {
public:
  virtual LoadInfo PreLoad() { return LoadInfo(); }
  virtual void Load() {}

  void RegisterType(std::string name, std::string wname, bool extended,
                    Data neutral, std::string defFunction) {
    typesPreloadData.push_back({name, wname, extended, neutral, defFunction});
  }
  //  void RegisterType(Type *t) { types.push_back(t); }

  void RegisterOperation(OpSymbol symbol, OpType opType,
                         std::string fromElementType, std::string toElementType,
                         std::string opFunction) {
    opPreloadData.push_back(
        {symbol, opType, fromElementType, toElementType, opFunction});
  }

  void RegisterLiteral(std::string name, std::string policyFunc,
                       std::string dataFunc, std::string compFunc) {
    litPreloadData.push_back({name, policyFunc, dataFunc, compFunc});
  }

  std::vector<
      std::tuple<std::string, std::string, bool, WyrmAPI::Data, std::string>>
  _GetTypeList() {
    return typesPreloadData;
  }

  std::vector<
      std::tuple<OpSymbol, OpType, std::string, std::string, std::string>>
  _GetOperations() {
    return opPreloadData;
  }
  std::vector<std::tuple<std::string, std::string, std::string, std::string>>
  _GetLiterals() {
    return litPreloadData;
  }

private:
  std::vector<
      std::tuple<std::string, std::string, bool, WyrmAPI::Data, std::string>>
      typesPreloadData;
  std::vector<
      std::tuple<OpSymbol, OpType, std::string, std::string, std::string>>
      opPreloadData;
  std::vector<std::tuple<std::string, std::string, std::string, std::string>>
      litPreloadData;
};
} // namespace WyrmAPI
