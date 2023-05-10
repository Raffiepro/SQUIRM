#pragma once

#include "../_base.h"
#include "lexer.h"
#include <vector>

using namespace WyrmAPI;

namespace Wyrm {

class Parser {
public:
  Parser(Book *book, std::vector<Token> tokens);
  Node *GetAST();

private:
  std::vector<WyrmAPI::Token> tokens;
  Book *book;

  std::vector<std::vector<WyrmAPI::TokenType>> opOrder = {
      {TokenType::MODULO},
      {TokenType::MULTIPLY, TokenType::DIVIDE},
      {TokenType::ADD, TokenType::SUBTRACT},
      {TokenType::GREATER_THAN, TokenType::LESSER_THAN, TokenType::NOT},
      {TokenType::NOT_EQUAL, TokenType::EQUAL, TokenType::GREATER_EQUAL_THAN,
       TokenType::LESSER_EQUAL_THAN, TokenType::AND, TokenType::OR}};

  std::vector<WyrmAPI::TokenType> assignations = {
      TokenType::ASSIGMENT,          TokenType::ASSIGMENT_ADD,
      TokenType::ASSIGMENT_SUBTRACT, TokenType::ASSIGMENT_MULTIPLY,
      TokenType::ASSIGMENT_DIVIDE,   TokenType::ASSIGMENT_MODULO};

  std::map<WyrmAPI::TokenType, WyrmAPI::TokenType> opMap = {
      {TokenType::ADD, TokenType::ASSIGMENT_ADD},
      {TokenType::SUBTRACT, TokenType::ASSIGMENT_SUBTRACT},
      {TokenType::DIVIDE, TokenType::ASSIGMENT_DIVIDE},
      {TokenType::MULTIPLY, TokenType::ASSIGMENT_MULTIPLY},
      {TokenType::MODULO, TokenType::ASSIGMENT_MODULO}};

  std::map<WyrmAPI::TokenType, OpSymbol> tokenToSymbol = {
      {ADD, OpSymbol::OP_ADD},
      {SUBTRACT, OpSymbol::OP_SUBTRACT}, // -
      {MULTIPLY, OpSymbol::OP_MUL},      // *
      {DIVIDE, OpSymbol::OP_DIV},        // /
      {MODULO, OpSymbol::OP_MOD},        // %
      {AMPERSAND, OpSymbol::OP_AMP},     // &
      {PIPE, OpSymbol::OP_PIPE},         // |
      {QUESTION_MARK, OpSymbol::OP_QM},
      {INV_QUESTION_MARK, OpSymbol::OP_IQM},
      {UP_ARROW, OpSymbol::OP_UP},
      {AT_SYMBOL, OpSymbol::OP_AT},
      {LEFT_SHIFT, OpSymbol::OP_LEFTSHIFT},
      {RIGHT_SHIFT, OpSymbol::OP_RIGHTSHIFT},
      {AND, OpSymbol::OP_AND},
      {OR, OpSymbol::OP_OR},
      {NOT, OpSymbol::OP_NOT},
      {EQUAL, OpSymbol::OP_EQ},
      {MORE_EQUAL, OpSymbol::OP_MEQ},
      {NOT_EQUAL, OpSymbol::OP_NEQ},
      {NOT_MORE_EQUAL, OpSymbol::OP_MNEQ},
      {GREATER_THAN, OpSymbol::OP_GT},
      {LESSER_THAN, OpSymbol::OP_LT},
      {GREATER_EQUAL_THAN, OpSymbol::OP_GEQ},
      {LESSER_EQUAL_THAN, OpSymbol::OP_LEQ},
      {DOLLAR, OpSymbol::OP_DOLLAR},           // $
      {ARROW_RIGHT, OpSymbol::OP_ARROW_RIGHT}, // ->
      {ARROW_LEFT, OpSymbol::OP_ARROW_LEFT}};

  Node *root;

  void GenerateCode(int from, int to, Node *parent);

  void ThrowError();

  void GetCodeFunction(Node **root, int from, int *end);
  void GetCodeLine(Node *root, int from, int to);
  void GetCodeConditional(Node **root, int from, int *end);
  void GetCodeWhile(Node **root, int from, int *end);
  void GetCodeReturn(Node **root, int from, int *end);
  void GetCodeFor(Node **root, int from, int *end);
  void GetCodeBreak(Node **root, int from, int *end);
  void GetCodeSkip(Node **root, int from, int *end);

  bool Eat(int pos, WyrmAPI::TokenType comp, int *from);

  int GetNext(int from, int lim, WyrmAPI::TokenType type);
  int GetNextCodeSep(int from, int lim);

  void GetArguments(int from, int to, std::vector<Node *> *parent);
  void GetFunctionParameters(int from, int to, std::vector<Node *> *container);
  void GetFunctionParameter(int from, int to, Node **writeNode);
  void GetAssignation(int from, int to, Node **writeNode);
  void GetAssignations(int from, int to, std::vector<Node *> *container);
  void GetConditional(int from, int *to, Node *pushNode);
  void GetCodeBlock(int from, int *to, Node *parent);

  void GetExpression(int from, int to, Node **writeNode);
  void GetLiteral(int index, Node **writeNode);

  bool CodeLoop(int *from, int *nF, Node *parent);

  bool ContainsAssignation(int from, int to);

  bool IsOf(std::vector<WyrmAPI::TokenType> list, WyrmAPI::TokenType type);
};
} // namespace Wyrm
