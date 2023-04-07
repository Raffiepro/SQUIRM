#include "lexer.h"
#include "../../api/wyrm.h"
#include "../libraries/library.h"
#include <iostream>
#include <string>

#define COMMENT '#'
#define SPACE ' '
#define NEW_LINE '\n'
#define TAB '\t'

using namespace That;

Token::Token(WyrmAPI::TokenType type, std::string value, int data) {
  this->type = type;
  this->value = value;
  this->data = data;
}

Token::Token(WyrmAPI::TokenType type, std::string value) {
  this->value = value;
  this->type = type;
}

Token::Token(WyrmAPI::TokenType type) { this->type = type; }

Token::Token(WyrmAPI::TokenType type, int data) {
  this->type = type;
  this->data = data;
}

Token::Token() { this->type = WyrmAPI::TokenType::ERROR; }

Token::~Token() {}

bool Token::IsLiteral() { return this->type == WyrmAPI::LITERAL; }

bool Token::IsIdentifier() { return this->type == WyrmAPI::IDENTIFIER; }

Lexer::Lexer(char *code, int codeSize, Book *book) {
  this->code = code;
  this->codeSize = codeSize;
  this->book = book;

  maxSearchLength = 0;
  std::vector<std::tuple<WyrmAPI::TokenType, std::string>> ort =
      GetOrtography();
  for (auto t : ort) {
    int c = std::get<1>(t).size();
    if (c > maxSearchLength)
      maxSearchLength = c;
  }
}

Lexer::~Lexer() {}

std::vector<std::tuple<WyrmAPI::TokenType, std::string>>
Lexer::GetOrtography() {
  return std::vector<std::tuple<WyrmAPI::TokenType, std::string>>(
      {{WyrmAPI::ADD, "+"},
       {WyrmAPI::SUBTRACT, "-"},  // -
       {WyrmAPI::MULTIPLY, "*"},  // *
       {WyrmAPI::DIVIDE, "/"},    // /
       {WyrmAPI::MODULO, "%"},    // %
       {WyrmAPI::AMPERSAND, "&"}, // &
       {WyrmAPI::PIPE, "|"},      // |
       {WyrmAPI::QUESTION_MARK, "?"},
       {WyrmAPI::INV_QUESTION_MARK, "¿"},
       {WyrmAPI::UP_ARROW, "^"},
       {WyrmAPI::AT_SYMBOL, "@"},
       {WyrmAPI::LEFT_SHIFT, "<<"},
       {WyrmAPI::RIGHT_SHIFT, ">>"},
       {WyrmAPI::AND, "&&"},
       {WyrmAPI::OR, "||"},
       {WyrmAPI::NOT, "!"},
       {WyrmAPI::EQUAL, "=="},
       {WyrmAPI::MORE_EQUAL, "==="},
       {WyrmAPI::NOT_EQUAL, "!="},
       {WyrmAPI::NOT_MORE_EQUAL, "!=="},
       {WyrmAPI::GREATER_THAN, ">"},
       {WyrmAPI::LESSER_THAN, "<"},
       {WyrmAPI::GREATER_EQUAL_THAN, ">="},
       {WyrmAPI::LESSER_EQUAL_THAN, "<="},
       {WyrmAPI::INCREMENT, "++"},
       {WyrmAPI::DECREMENT, "--"},
       {WyrmAPI::ASSIGMENT, "="},
       {WyrmAPI::SEMICOLON, ";"},
       {WyrmAPI::ASSIGMENT_ADD, "+="},
       {WyrmAPI::ASSIGMENT_SUBTRACT, "-="},
       {WyrmAPI::ASSIGMENT_MULTIPLY, "*="},
       {WyrmAPI::ASSIGMENT_DIVIDE, "/="},
       {WyrmAPI::ASSIGMENT_MODULO, "%="},
       {WyrmAPI::COMMA, ","},                // ,
       {WyrmAPI::POINT, "."},                // .
       {WyrmAPI::PARENTHESIS_OPEN, "("},     // (
       {WyrmAPI::PARENTHESIS_CLOSE, ")"},    // )
       {WyrmAPI::SQUARE_BRACKET_OPEN, "["},  // [
       {WyrmAPI::SQUARE_BRACKET_CLOSE, "]"}, // ]
       {WyrmAPI::CURLY_BRACKET_OPEN, "{"},   // {
       {WyrmAPI::CURLY_BRACKET_CLOSE, "}"},  // }
       {WyrmAPI::DOLLAR, "$"},               // $
       {WyrmAPI::TWO_POINTS, ":"},           // :
       {WyrmAPI::ARROW_RIGHT, "->"},         // ->
       {WyrmAPI::WIDE_ARROW_RIGHT, "=>"},
       {WyrmAPI::ARROW_LEFT, "<-"},
       {WyrmAPI::WIDE_ARROW_LEFT, "<="},
       {WyrmAPI::LONG_ARROW_RIGHT, "-->"},
       {WyrmAPI::LONG_ARROW_LEFT, "<--"},
       {WyrmAPI::LONG_WIDE_ARROW_RIGHT, "==>"},
       {WyrmAPI::LONG_WIDE_ARROW_LEFT, "<=="},
       {WyrmAPI::QUOT, "'"},            // '
       {WyrmAPI::DOUBLE_QUOT, "\""},    // "
       {WyrmAPI::IF, "if"},             // if
       {WyrmAPI::ELSE, "else"},         // else
       {WyrmAPI::WHILE, "while"},       // while
       {WyrmAPI::FOR, "for"},           // for
       {WyrmAPI::RETURN, "return"},     // return
       {WyrmAPI::BREAK, "break"},       // stop
       {WyrmAPI::CONTINUE, "continue"}, // skip
       {WyrmAPI::FUNCTION_DECLARATION, "func"},
       {WyrmAPI::MODULE_DECLARATION, "use"},
       {WyrmAPI::IMPORT_DECLARATION, "import"}});
}

/*
De un codi doncs torna tokens!
*/
std::vector<Token> *Lexer::GetTokens() { return &tokenList; }

int Lexer::isNumber(char c) {
  if (c >= 48 && c <= 57)
    return true;
  return false;
}

int Lexer::isEmpty(char c) { return c == SPACE || c == NEW_LINE || c == TAB; }

void Lexer::flush(int *next) {
  int pos = *next;
  while (isEmpty(code[pos]))
    pos++;
  *next = pos;
}

bool Lexer::NotSymbol(char c) {
  return (c <= '9' && c >= '0') || (c >= 'A' && c <= 'Z') ||
         (c >= 'a' && c <= 'z');
}

int Lexer::isSentenceEnd(char c) { return c == ';' || c == NEW_LINE; }

int Lexer::isSeparator(char c) { return isSentenceEnd(c) || isEmpty(c); }

int Lexer::isEnd(int pos) { return pos >= codeSize; }

void Lexer::addError() { tokenList.push_back(Token()); }

/*
void Lexer::getString(int *next) {
  int pos = *next;
  std::string s = "";

  int start = pos;

  char check = code[pos];
  pos++;
  while (code[pos] != check) {
    if (code[pos] == '\\') {
      if (!isEnd(pos + 1)) {
        if (code[pos + 1] == check) {
          s += check;
          pos += 2;
          continue;
        }
      } else {
        // Error
        addError();
        return;
      }
    }
    s += code[pos];
    pos++;
  }

  *next = pos + 1;
  tokenList.push_back(Token(Token::L_STRING, s));
  // Sin error
}
*/
void Lexer::skipComment(int *next) {
  if (code[*next] == COMMENT) {
    int pos = *next;
    if (!isEnd(pos + 1)) {
      if (code[pos + 1] == COMMENT) {
        pos += 2;
        while (!(code[pos] == COMMENT && code[pos + 1] == COMMENT &&
                 !isEnd(pos + 1)))
          pos++;
      } else
        while (code[pos] != NEW_LINE && !isEnd(pos))
          pos++;
    }

    *next = pos + 1;
  }
}

int Lexer::CheckLiterals(int *next) {
  if (isEnd(*next))
    return 1;

  for (int i = 0; i < book->literals.size(); i++) {
    WyrmAPI::LexerInfo r = book->literals[i].policy(code + *next);
    std::string s;
    if (r.valid) {
      std::string value = r.value;
      *next += r.end;
      tokenList.push_back(Token(WyrmAPI::TokenType::LITERAL, value, i));
      return 1;
    }
  }

  return 0;
}

int Lexer::CheckTypes(int *next) {
  if (isEnd(*next))
    return 1;

  int size = 0;
  while (!isEnd(*next + size)) {
    // Comprovem que la posició *next + size es lletra i tal
    if (NotSymbol(code[*next + size]))
      size++;
    else
      break;
  }

  for (int i = 0; i < book->types.size(); i++) {
    std::string name = book->types[i].name;
    bool valid = true;

    for (int j = 0; j < name.size(); j++) {
      if (isEnd(*next + j)) {
        valid = false;
        break;
      }
      if (name[j] != code[*next + j]) {
        valid = false;
        break;
      }
    }

    if (valid) {
      tokenList.push_back(Token(WyrmAPI::TokenType::TYPE, i));
      return 1;
    }
  }

  return 0;
}

int Lexer::CheckKeywords(int *next) {

  if (isEnd(*next))
    return 1;
  if (isEmpty(code[*next]))
    return 1;

  // Aqui cal comprovar que comença per una lletra i tal
  int pos = *next;
  std::string word = "";

  auto ort = GetOrtography();

  WyrmAPI::TokenType bestType = WyrmAPI::TokenType::ERROR;
  int bestTypeLength = 0;

  for (int i = 0; i < maxSearchLength; i++) {
    word += code[pos + i];
    for (auto pair : ort) {
      if (std::get<1>(pair) == word) {
        bestType = std::get<0>(pair);
        bestTypeLength = i;
      }
    }
  }

  if (bestType == WyrmAPI::TokenType::ERROR)
    return 0;

  // Si se puede pues añadimos el token
  *next += bestTypeLength;
  tokenList.push_back(Token(bestType));
  return 1;
}

int Lexer::CheckIdentifiers(int *next) {
  // Anem ciclant fins que ens trobem alguna cosa que no es lletra o numero
  std::string identifier = "";
  int pos = *next;
  while (NotSymbol(code[pos])) {
    identifier += code[pos];
    pos++;
  }

  tokenList.push_back(Token(WyrmAPI::TokenType::IDENTIFIER, identifier));
  *next += pos;

  return 1;
}

int Lexer::GenerateTokens() {
  std::cout << codeSize << std::endl;
  for (int i = 0; i < codeSize;) {
    std::cout << i << std::endl;
    skipComment(&i);

    if (CheckKeywords(&i)) {
      flush(&i);
      continue;
    }
    if (CheckTypes(&i)) {
      flush(&i);
      continue;
    }
    if (CheckLiterals(&i)) {
      flush(&i);
      continue;
    }
    CheckIdentifiers(&i);
    flush(&i);

    // std::cout << code[i] << std::endl;
  }

  return 0;
}
