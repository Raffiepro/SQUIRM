#pragma once

#include <map>
#include <string>
#include <vector>

#include "../libraries/library.h"

namespace That {

class Token {
public:
  Token(WyrmAPI::TokenType type, int data);
  Token(WyrmAPI::TokenType type, std::string value, int data);
  Token(WyrmAPI::TokenType type, std::string value);
  Token(WyrmAPI::TokenType type);

  Token();
  ~Token();

  bool IsLiteral();
  bool IsIdentifier();

  std::string value;
  WyrmAPI::TokenType type;
  int data;
};

class Lexer {
public:
  Lexer(char *code, int codeSize, Book *book);
  ~Lexer();
  std::vector<Token> *GetTokens();
  int GenerateTokens();

private:
  std::vector<std::tuple<WyrmAPI::TokenType, std::string>> GetOrtography();
  int maxSearchLength;

  void flush(int *next);

  int isNumber(char c);
  int isEmpty(char c);
  int isSentenceEnd(char c);
  int isSeparator(char c);
  int isEnd(int i);
  bool NotSymbol(char c);

  void skipComment(int *next);
  int CheckLiterals(int *next);
  int CheckTypes(int *next);
  int CheckKeywords(int *next);
  int CheckIdentifiers(int *next);

  int getNumber(int *next);
  void getString(int *next);

  void addError();

  char *code;
  int codeSize;

  std::vector<Token> tokenList;
  Book *book;
};

} // namespace That
