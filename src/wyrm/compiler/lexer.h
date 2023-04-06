#pragma once

#include <map>
#include <string>
#include <vector>

#include "../libraries/library.h"

namespace That {

class Token {
public:
  enum TokenType {
    ERROR,

    TYPE,

    // OP BINARIES
    S_PLUS,     // +            X
    S_SUBTRACT, // -            X
    S_MULTIPLY, // *            X
    S_DIVIDE,   // /            X
    S_MODULO,   // %            X

    S_AND, // &&
    S_OR,  // ||
    S_NOT, // !

    C_EQUAL,              // ==           X
    C_NOT_EQUAL,          // !=           X
    C_GREATER_THAN,       // >            X
    C_LESSER_THAN,        // <            X
    C_GREATER_EQUAL_THAN, // >=           X
    C_LESSER_EQUAL_THAN,  // <=           X

    S_INCREMENT, // ++           X
    S_DECREMENT, // --

    A_ASSIGMENT, // =            X
    A_ADD,       // +=           X
    A_SUBTRACT,  // -=           X
    A_MULTIPLY,  // *=           X
    A_DIVIDE,    // /=           X
    A_MODULO,    // %=           X

    COMMA,                // ,        X
    POINT,                // .        X
    PARENTHESIS_OPEN,     // (        X
    PARENTHESIS_CLOSE,    // )        X
    SQUARE_BRACKET_OPEN,  // [        X
    SQUARE_BRACKET_CLOSE, // ]        X
    CURLY_BRACKET_OPEN,   // {        X
    CURLY_BRACKET_CLOSE,  // }        X
    DOLLAR,               // $
    SEMICOLON,            // ;        X
    TWO_POINTS,           // :        X
    ARROW,                // ->

    K_IF,       // if        X
    K_ELSE,     // else      X
    K_WHILE,    // while     X
    K_FOR,      // for
    K_RETURN,   // return    X
    K_BREAK,    // stop      X
    K_CONTINUE, // skip      X

    LITERAL, // 3        X

    FUNCTION_DECLARATION, // func     X
    MODULE_DECLARATION,   // use      X
    IMPORT_DECLARATION,   // import   X

    IDENTIFIER // algo     X

  };

  Token(TokenType type, std::string value, int data);
  Token(TokenType type);

  Token();
  ~Token();

  bool IsLiteral();
  bool IsIdentifier();

  std::string value;
  TokenType type;
  int data;
};

class Lexer {
  enum Symbols {
    POINT,
    SPACE,
    TAB,
    NEWLINE,
    SEMICOLON,
    TWO_POINTS,
    COMMENT,
    DOUBLE_QUOT,
    QUOT,
    ESCAPE,
    COMMA,
    PARENTESIS_O,
    PARENTESIS_C,
    KEY_O,
    KEY_C,
    CLAUDATOR_O,
    CLAUDATOR_C,
    DOLLAR,
    BAR,

    MINUS,
    PLUS,
    MULTI,
    DIVIDE,
    PERCENT,
    FISH_O,
    FISH_C,
    EXCLAMATION,
  };

  enum Keywords {
    FUNC,
    MODULE,
    IMPORT,

    IF,
    ELSE,
    WHILE,
    RETURN,
    BREAK,
    CONTINUE,
    FOR,

    INT,
    REAL,
    STRING,
    BOOLEAN,
    TRUE,
    FALSE,
    _NULL,
  };

  std::map<std::string, Keywords> typeKeyword = {
      {"func", FUNC},     {"use", MODULE},    {"import", IMPORT},
      {"if", IF},         {"else", ELSE},     {"while", WHILE},
      {"for", FOR},       {"return", RETURN}, {"stop", BREAK},
      {"skip", CONTINUE}, {"int", INT},       {"real", REAL},
      {"string", STRING}, {"bool", BOOLEAN},  {"True", TRUE},
      {"False", FALSE},   {"Null", _NULL}};

  std::map<Symbols, char> typeSymbol = {
      {POINT, '.'},        {SPACE, ' '},       {TAB, '\t'},
      {NEWLINE, '\n'},     {SEMICOLON, ';'},   {TWO_POINTS, ':'},
      {COMMENT, '#'},      {DOUBLE_QUOT, '"'}, {QUOT, '\''},
      {ESCAPE, '\\'},      {COMMA, ','},       {PARENTESIS_O, '('},
      {PARENTESIS_C, ')'}, {KEY_O, '{'},       {KEY_C, '}'},
      {CLAUDATOR_O, '['},  {CLAUDATOR_C, ']'}, {MINUS, '-'},
      {PLUS, '+'},         {MULTI, '*'},       {DIVIDE, '/'},
      {PERCENT, '%'},      {FISH_O, '<'},      {FISH_C, '>'},
      {EXCLAMATION, '!'},  {DOLLAR, '$'},      {BAR, '|'}};

  std::map<std::string, Token::TokenType> typeOperation = {
      {"+", Token::S_PLUS},
      {"-", Token::S_SUBTRACT},
      {"*", Token::S_MULTIPLY},
      {"/", Token::S_DIVIDE},
      {"%", Token::S_MODULO},
      {"!", Token::S_NOT},
      {"&&", Token::S_AND},
      {"||", Token::S_OR},
      {"++", Token::S_INCREMENT},
      {"--", Token::S_DECREMENT},
      {"=", Token::A_ASSIGMENT},
      {"==", Token::C_EQUAL},
      {"+=", Token::A_ADD},
      {"-=", Token::A_SUBTRACT},
      {"*=", Token::A_MULTIPLY},
      {"/=", Token::A_DIVIDE},
      {"%=", Token::A_MODULO},
      {">", Token::C_GREATER_THAN},
      {"<", Token::C_LESSER_THAN},
      {">=", Token::C_GREATER_EQUAL_THAN},
      {"<=", Token::C_LESSER_EQUAL_THAN},
      {"!=", Token::C_NOT_EQUAL},
      {"=>", Token::ARROW}};

public:
  Lexer(char *code, int codeSize, Book *book);
  ~Lexer();
  std::vector<Token> *GetTokens();
  int GenerateTokens();

private:
  std::string nextWord(int pos, int *nextPos);
  void flush(int *next);

  int isNumber(char c);
  int isEmpty(char c);
  int isSemicolon(char c);
  int isSeparator(char c);
  int isEnd(int i);
  int isComment(char c);
  int isPoint(char c);
  int isQuot(char c);
  int isDoubleQuot(char c);
  int isSymbol(char c);
  int isComma(char c);
  int isOParentesis(char c);
  int isCParentesis(char c);
  int isParentesis(char c);
  int isOClaudator(char c);
  int isCClaudator(char c);
  int isClaudator(char c);
  int isOKey(char c);
  int isCKey(char c);
  int isKey(char c);
  int isTwoPoints(char c);

  void skipComment(int *next);
  int checkLiterals(int *next);
  int checkKeywords(int *next);
  int checkSymbols(int *next);
  int checkOperations(int *next);

  int getNumber(int *next);
  void getString(int *next);

  void addError();

  char *code;
  int codeSize;

  std::vector<Token> tokenList;
  Book *book;
};

} // namespace That