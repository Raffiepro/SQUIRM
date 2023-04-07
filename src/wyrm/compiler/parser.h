#pragma once

#include <vector>

#include "../vm/data.h"
#include "lexer.h"
#include "nodes.h"

namespace That {

class Parser {
public:
  Parser(Book *book, std::vector<That::Token> tokens);

  Nodes::Node *GetAST();

private:
  std::vector<That::Token> tokens;
  Book *book;

  std::vector<std::vector<WyrmAPI::TokenType>> opOrder = {
      {WyrmAPI::TokenType::MODULO},
      {WyrmAPI::TokenType::MULTIPLY, WyrmAPI::TokenType::DIVIDE},
      {WyrmAPI::TokenType::ADD, WyrmAPI::TokenType::SUBTRACT},
      {WyrmAPI::TokenType::GREATER_THAN, WyrmAPI::TokenType::LESSER_THAN,
       WyrmAPI::TokenType::NOT},
      {WyrmAPI::TokenType::NOT_EQUAL, WyrmAPI::TokenType::EQUAL,
       WyrmAPI::TokenType::GREATER_EQUAL_THAN,
       WyrmAPI::TokenType::LESSER_EQUAL_THAN, WyrmAPI::TokenType::AND,
       WyrmAPI::TokenType::OR}};

  std::vector<WyrmAPI::TokenType> assignations = {
      WyrmAPI::TokenType::ASSIGMENT,
      WyrmAPI::TokenType::ASSIGMENT_ADD,
      WyrmAPI::TokenType::ASSIGMENT_SUBTRACT,
      WyrmAPI::TokenType::ASSIGMENT_MULTIPLY,
      WyrmAPI::TokenType::ASSIGMENT_DIVIDE,
      WyrmAPI::TokenType::ASSIGMENT_MODULO};

  std::map<WyrmAPI::TokenType, WyrmAPI::TokenType> opMap = {
      {WyrmAPI::TokenType::ADD, WyrmAPI::TokenType::ASSIGMENT_ADD},
      {WyrmAPI::TokenType::SUBTRACT, WyrmAPI::TokenType::ASSIGMENT_SUBTRACT},
      {WyrmAPI::TokenType::DIVIDE, WyrmAPI::TokenType::ASSIGMENT_DIVIDE},
      {WyrmAPI::TokenType::MULTIPLY, WyrmAPI::TokenType::ASSIGMENT_MULTIPLY},
      {WyrmAPI::TokenType::MODULO, WyrmAPI::TokenType::ASSIGMENT_MODULO}};

  std::map<WyrmAPI::TokenType, WyrmAPI::OpSymbol> tokenToSymbol = {
      {WyrmAPI::ADD, WyrmAPI::OpSymbol::OP_ADD},
      {WyrmAPI::SUBTRACT, WyrmAPI::OpSymbol::OP_SUBTRACT}, // -
      {WyrmAPI::MULTIPLY, WyrmAPI::OpSymbol::OP_MUL},      // *
      {WyrmAPI::DIVIDE, WyrmAPI::OpSymbol::OP_DIV},        // /
      {WyrmAPI::MODULO, WyrmAPI::OpSymbol::OP_MOD},        // %
      {WyrmAPI::AMPERSAND, WyrmAPI::OpSymbol::OP_AMP},     // &
      {WyrmAPI::PIPE, WyrmAPI::OpSymbol::OP_PIPE},         // |
      {WyrmAPI::QUESTION_MARK, WyrmAPI::OpSymbol::OP_QM},
      {WyrmAPI::INV_QUESTION_MARK, WyrmAPI::OpSymbol::OP_IQM},
      {WyrmAPI::UP_ARROW, WyrmAPI::OpSymbol::OP_UP},
      {WyrmAPI::AT_SYMBOL, WyrmAPI::OpSymbol::OP_AT},
      {WyrmAPI::LEFT_SHIFT, WyrmAPI::OpSymbol::OP_LEFTSHIFT},
      {WyrmAPI::RIGHT_SHIFT, WyrmAPI::OpSymbol::OP_RIGHTSHIFT},
      {WyrmAPI::AND, WyrmAPI::OpSymbol::OP_AND},
      {WyrmAPI::OR, WyrmAPI::OpSymbol::OP_OR},
      {WyrmAPI::NOT, WyrmAPI::OpSymbol::OP_NOT},
      {WyrmAPI::EQUAL, WyrmAPI::OpSymbol::OP_EQ},
      {WyrmAPI::MORE_EQUAL, WyrmAPI::OpSymbol::OP_MEQ},
      {WyrmAPI::NOT_EQUAL, WyrmAPI::OpSymbol::OP_NEQ},
      {WyrmAPI::NOT_MORE_EQUAL, WyrmAPI::OpSymbol::OP_MNEQ},
      {WyrmAPI::GREATER_THAN, WyrmAPI::OpSymbol::OP_GT},
      {WyrmAPI::LESSER_THAN, WyrmAPI::OpSymbol::OP_LT},
      {WyrmAPI::GREATER_EQUAL_THAN, WyrmAPI::OpSymbol::OP_GEQ},
      {WyrmAPI::LESSER_EQUAL_THAN, WyrmAPI::OpSymbol::OP_LEQ},
      {WyrmAPI::DOLLAR, WyrmAPI::OpSymbol::OP_DOLLAR},           // $
      {WyrmAPI::ARROW_RIGHT, WyrmAPI::OpSymbol::OP_ARROW_RIGHT}, // ->
      {WyrmAPI::ARROW_LEFT, WyrmAPI::OpSymbol::OP_ARROW_LEFT}};

  Nodes::Node *root;

  void GenerateCode(int from, int to, Nodes::Node *parent);

  void ThrowError();

  void GetCodeFunction(Nodes::Node **root, int from, int *end);
  void GetCodeLine(Nodes::Node *root, int from, int to);
  void GetCodeConditional(Nodes::Node **root, int from, int *end);
  void GetCodeWhile(Nodes::Node **root, int from, int *end);
  void GetCodeReturn(Nodes::Node **root, int from, int *end);
  void GetCodeFor(Nodes::Node **root, int from, int *end);
  void GetCodeBreak(Nodes::Node **root, int from, int *end);
  void GetCodeSkip(Nodes::Node **root, int from, int *end);

  bool Eat(int pos, WyrmAPI::TokenType comp, int *from);

  int GetNext(int from, int lim, WyrmAPI::TokenType type);
  int GetNextCodeSep(int from, int lim);

  void GetArguments(int from, int to, std::vector<Nodes::Node *> *parent);
  void GetFunctionParameters(int from, int to,
                             std::vector<Nodes::Node *> *container);
  void GetFunctionParameter(int from, int to, Nodes::Node **writeNode);
  void GetAssignation(int from, int to, Nodes::Node **writeNode);
  void GetAssignations(int from, int to, std::vector<Nodes::Node *> *container);
  void GetConditional(int from, int *to, Nodes::Node *pushNode);
  void GetCodeBlock(int from, int *to, Nodes::Node *parent);

  void GetExpression(int from, int to, Nodes::Node **writeNode);
  void GetLiteral(int index, Nodes::Node **writeNode);

  bool CodeLoop(int *from, int *nF, Nodes::Node *parent);

  bool ContainsAssignation(int from, int to);

  bool IsOf(std::vector<WyrmAPI::TokenType> list, WyrmAPI::TokenType type);
};
} // namespace That
