#pragma once

#include "termcolor.hpp"

#define N_SYMBOLS 27

#include <map>
#include <string>
#include <tuple>
#include <vector>

namespace WyrmAPI {
struct Data {
  int num;
  void *data;

  Data(int num) { this->num = num; }

  Data() {}
};

namespace Debug {
template <typename T> void Log(T t) {
  std::cout << termcolor::grey << t << termcolor::reset;
}

template <typename T> void LogError(T t) {
  std::cout << termcolor::red << t << termcolor::reset << std::endl;
}

template <typename T> void LogImportant(T t) {
  std::cout << termcolor::yellow << t << termcolor::reset;
}

template <typename T> void LogOutput(T t) {
  std::cout << termcolor::color<120, 255, 0> << t << termcolor::reset;
}

template <typename T> void Print(T t) {
  std::cout << termcolor::green << t << termcolor::reset;
}
}; // namespace Debug

enum NodeType {
  NODE,
  ERROR_NODE,
  DECLARATION,
  ASSIGNATION,
  REFERENCE,
  PARAMETER,
  TYPE_NODE,
  IF_NODE,
  WHILE_NODE,
  FOR_NODE,
  BREAK_NODE,
  SKIP,
  RETURN_NODE,
  FUNCTION,
  DEF_FUNCTION,
  NODE_ERROR,
  EXP_BINARY,
  EXP_UNARY,
  EXP_CALL,
  VALUE,
};

struct Atom {
  Data *data;
  int typeId;
};

class Node {

public:
  // Node(NodeType type);
  // void Execute(); // Això per execució un cop construida la estructura del
  // codi
  Node(NodeType type) {
    this->type = type;
    this->children.reserve(1);
    this->allocable = false;
  };
  Node() {
    this->type = NodeType::NODE;
    this->children.reserve(1);
    this->allocable = false;
  }
  ~Node() {
    for (int i = 0; i < children.size(); i++) {
      delete children[i];
    }
  }

  std::vector<Node *> children;
  NodeType type;

  bool allocable = false;
  int nd;
  std::string sData;
  Atom *atom = NULL;

  void Debug() {
    std::map<NodeType, std::string> trans = {{NODE, "NODE"},
                                             {ERROR_NODE, "ERROR"},
                                             {DECLARATION, "DECLARATION"},
                                             {ASSIGNATION, "ASSIGNATION"},
                                             {REFERENCE, "REFERENCE"},
                                             {PARAMETER, "PARAMETER"},
                                             {TYPE_NODE, "TYPE"},
                                             {IF_NODE, "IF"},
                                             {WHILE_NODE, "WHILE"},
                                             {FUNCTION, "FUNCTION"},
                                             {DEF_FUNCTION, "DEF_FUNCTION"},
                                             {RETURN_NODE, "RETURN"},
                                             {FOR_NODE, "FOR"},
                                             {BREAK_NODE, "BREAK"},
                                             {SKIP, "SKIP"},
                                             {NODE_ERROR, "NODE_ERROR"},
                                             {EXP_BINARY, "EXP_BINARY"},
                                             {EXP_UNARY, "EXP_UNARY"},
                                             {EXP_CALL, "EXP_CALL"},
                                             {VALUE, "VALUE"}};

    std::cout << "[ ";
    if (trans.find(this->type) == trans.end())
      std::cout << "type: " << termcolor::red << "UNDEFINED" << termcolor::reset
                << ", ";
    else
      std::cout << "type: " << termcolor::green << trans[this->type]
                << termcolor::reset;

    if (this->children.size() > 0) {
      std::cout << ", fills: ";
      for (int i = 0; i < this->children.size(); i++) {
        this->children[i]->Debug();
      }
    }

    if (this->atom != NULL)
      std::cout << ", atom: " << this->atom->data->num;
    std::cout << " ]";
  }

  bool IsValue() { return (this->type == NodeType::VALUE); }
  bool IsExpression() {
    return (IsValue() || this->type == NodeType::EXP_BINARY ||
            this->type == NodeType::EXP_UNARY ||
            this->type == NodeType::EXP_CALL);
  }

  void SetDataString(std::string s) { this->sData = s; }
  std::string GetDataString() { return this->sData; }
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


struct RunnerInfo {
  std::string runFunction;
  bool live;
};

class TreeCode {
  
  public:
    TreeCode(Node* root){
      this->root = root;
    }

    std::vector<std::string>& GetDependencies(){
      return deps;
    }
    
    Node* root;
  private:
    std::vector<std::string> deps;

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

  void RegisterRunner(std::string name, RunnerInfo runnerInfo){
      runnerPreloadData.push_back({name, runnerInfo});
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

  std::vector<std::tuple<std::string, RunnerInfo>> _GetRunners(){
    return runnerPreloadData;
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
  std::vector<std::tuple<std::string, RunnerInfo>> runnerPreloadData;
};

} // namespace WyrmAPI
