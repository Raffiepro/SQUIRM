#include "lexer.h"
#include "../libraries/library.h"
#include <iostream>
#include <string>

using namespace That;

Token::Token(TokenType type, std::string value, int data) {
  this->type = type;
  this->value = value;
  this->data = data;
}

Token::Token(TokenType type) { this->type = type; }

Token::Token() { this->type = TokenType::ERROR; }

Token::~Token() {}

bool Token::IsLiteral() { return this->type >= LITERAL; }

bool Token::IsIdentifier() { return this->type == IDENTIFIER; }

// ---------------------------------------------------------------------------

Lexer::Lexer(char *code, int codeSize, Book *book) {
  this->code = code;
  this->codeSize = codeSize;
  this->book = book;
}

Lexer::~Lexer() {}

/*
De un codi doncs torna tokens!
*/
std::vector<Token> *Lexer::GetTokens() { return &tokenList; }

std::string Lexer::nextWord(int pos, int *nextPos) {
  std::string nWord = "";
  while (!isEnd(pos) && !isSymbol(code[pos])) {
    nWord += code[pos];
    pos++;
    if (isEmpty(code[pos]) || isSymbol(code[pos]))
      break;
  }
  *nextPos = pos;
  return nWord;
}

int Lexer::isNumber(char c) {
  if (c >= 48 && c <= 57)
    return true;
  return false;
}

int Lexer::isEmpty(char c) {
  return c == typeSymbol[Symbols::SPACE] || c == typeSymbol[Symbols::NEWLINE] ||
         c == typeSymbol[Symbols::TAB];
}

void Lexer::flush(int *next) {
  int pos = *next;
  while (isEmpty(code[pos]))
    pos++;
  *next = pos;
}

int Lexer::isSemicolon(char c) { return c == typeSymbol[Symbols::SEMICOLON]; }

int Lexer::isSeparator(char c) { return 0; }

int Lexer::isComment(char c) { return c == typeSymbol[Symbols::COMMENT]; }

int Lexer::isEnd(int pos) { return pos >= codeSize; }

int Lexer::isPoint(char c) { return c == typeSymbol[Symbols::POINT]; }

int Lexer::isQuot(char c) { return c == typeSymbol[Symbols::QUOT]; }

int Lexer::isDoubleQuot(char c) {
  return c == typeSymbol[Symbols::DOUBLE_QUOT];
}

int Lexer::isComma(char c) { return c == typeSymbol[Symbols::COMMA]; }

int Lexer::isOParentesis(char c) {
  return c == typeSymbol[Symbols::PARENTESIS_O];
}

int Lexer::isCParentesis(char c) {
  return c == typeSymbol[Symbols::PARENTESIS_C];
}

int Lexer::isParentesis(char c) { return isOParentesis(c) || isCParentesis(c); }

int Lexer::isOClaudator(char c) {
  return c == typeSymbol[Symbols::CLAUDATOR_O];
}

int Lexer::isCClaudator(char c) {
  return c == typeSymbol[Symbols::CLAUDATOR_C];
}

int Lexer::isClaudator(char c) { return isCClaudator(c) || isOClaudator(c); }

int Lexer::isOKey(char c) { return c == typeSymbol[Symbols::KEY_O]; }

int Lexer::isCKey(char c) { return c == typeSymbol[Symbols::KEY_C]; }

int Lexer::isKey(char c) { return isOKey(c) || isCKey(c); }

int Lexer::isTwoPoints(char c) { return c == typeSymbol[Symbols::TWO_POINTS]; }

int Lexer::isSymbol(char c) {
  for (auto &it : typeSymbol) {
    if (it.second == c) {
      return 1;
    }
  }

  return 0;
}

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
  if (isComment(code[*next])) {
    int pos = *next;
    if (!isEnd(pos + 1)) {
      if (isComment(code[pos + 1])) {
        pos += 2;
        while (!(code[pos] == typeSymbol[Symbols::COMMENT] &&
                 code[pos + 1] == typeSymbol[Symbols::COMMENT]) &&
               !isEnd(pos + 1))
          pos++;
      } else
        while (code[pos] != typeSymbol[Symbols::NEWLINE] && !isEnd(pos))
          pos++;
    }

    *next = pos + 1;
  }
}

int Lexer::checkLiterals(int *next) {
  if (isEnd(*next))
    return 1;
  // Aqui hauriem de ciclar per totes les declaracions de literals per les
  // llibreries

  for (int i = 0; i < book->literals.size(); i++) {
    ThatAPI::LexerInfo r = book->literals[i].policy(code + *next);
    std::string s;
    if (r.valid) {
      std::string value = r.value;
      *next += r.end;
      tokenList.push_back(Token(Token::LITERAL, value, i));
      break;
    }
  }

  char c = code[*next];
  if (isNumber(c) || isPoint(c)) {
    if (getNumber(next))
      return 0;
  } else if (isQuot(c) || isDoubleQuot(c)) {
    getString(next);
    return 0;
  }

  flush(next);
  return 1;
}

int Lexer::checkOperations(int *next) {
  if (isEnd(*next))
    return 1;
  if (isEmpty(code[*next]))
    flush(next);

  int pos = *next;
  int start = pos;
  // Bueno pues a comprovar
  std::string test(1, code[*next]);
  int i;
  for (i = 1; i < 2; i++) {
    if (isEnd(pos + i)) {
      break;
    }
    test += code[pos + i];
  }

  bool done = false;
  for (i--; i >= 0; i--) {
    if (typeOperation.count(test)) {
      tokenList.push_back(Token(typeOperation[test]));
      pos += i + 1;
      *next = pos;
      done = true;
      break;
    }
    test = test.substr(0, i);
  }

  flush(next);
  if (done)
    return 0;
  return 1;
}

int Lexer::checkKeywords(int *next) {

  if (isEnd(*next))
    return 1;
  if (isEmpty(code[*next]))
    return 1;
  if (isSymbol(code[*next]))
    return 1;
  if (isNumber(code[*next]))
    return 1;

  int pos = *next;
  std::string word;

  int nextPos = pos;
  word = nextWord(pos, &nextPos);

  int typeId;
  if (typeKeyword.count(word)) {
    // Aixo es podria agilitzar amb un bonic map
    switch (typeKeyword[word]) {
    case FUNC:
      /* code */
      tokenList.push_back(Token(Token::FUNCTION_DECLARATION, pos));
      break;
    case MODULE:
      tokenList.push_back(Token(Token::MODULE_DECLARATION, pos));
      break;
    case IMPORT:
      tokenList.push_back(Token(Token::IMPORT_DECLARATION, pos));
      break;
    case IF:
      tokenList.push_back(Token(Token::K_IF, pos));
      break;
    case ELSE:
      tokenList.push_back(Token(Token::K_ELSE, pos));
      break;
    case WHILE:
      tokenList.push_back(Token(Token::K_WHILE, pos));
      break;
    case FOR:
      tokenList.push_back(Token(Token::K_FOR, pos));
      break;
    case RETURN:
      tokenList.push_back(Token(Token::K_RETURN, pos));
      break;
    case BREAK:
      tokenList.push_back(Token(Token::K_BREAK, pos));
      break;
    case CONTINUE:
      tokenList.push_back(Token(Token::K_CONTINUE, pos));
      break;
    case TRUE:
      tokenList.push_back(Token(Token::L_TRUE, pos));
      break;
    case FALSE:
      tokenList.push_back(Token(Token::L_FALSE, pos));
      break;
    case _NULL:
      tokenList.push_back(Token(Token::L_NULL, pos));
      break;
    default:
      /* Ha de ser una reference */
      typeId = book->GetTypeFromName(word);

      if (typeId != -1) {
        Token t = Token(Token::TYPE, pos);
        t.value = typeId;
        tokenList.push_back(t);
      }

      break;
    }
  } else {
    tokenList.push_back(Token(Token::IDENTIFIER, word, pos));
  }

  *next = nextPos;

  flush(next);
  return 0;
}

int Lexer::checkSymbols(int *next) {
  if (isEnd(*next))
    return 0;
  switch (code[*next]) {
  case '.':
    tokenList.push_back(Token(Token::POINT, *next));
    break;
  case ',':
    tokenList.push_back(Token(Token::COMMA, *next));
    break;
  case ';':
    tokenList.push_back(Token(Token::SEMICOLON, *next));
    break;
  case ':':
    tokenList.push_back(Token(Token::TWO_POINTS, *next));
    break;
  case '(':
    tokenList.push_back(Token(Token::PARENTHESIS_OPEN, *next));
    break;
  case ')':
    tokenList.push_back(Token(Token::PARENTHESIS_CLOSE, *next));
    break;
  case '[':
    tokenList.push_back(Token(Token::SQUARE_BRACKET_OPEN, *next));
    break;
  case ']':
    tokenList.push_back(Token(Token::SQUARE_BRACKET_CLOSE, *next));
    break;
  case '{':
    tokenList.push_back(Token(Token::CURLY_BRACKET_OPEN, *next));
    break;
  case '}':
    tokenList.push_back(Token(Token::CURLY_BRACKET_CLOSE, *next));
    break;
  case '$':
    tokenList.push_back(Token(Token::DOLLAR, *next));
    break;
  /* case '!':
      tokenList.push_back(Token(Token::S_NOT));
      break; */
  default:
    return 1;
  }
  *next += 1;
  flush(next);
  return 0;
}

int Lexer::GenerateTokens() {
  for (int i = 0; i < code.size();) {
    skipComment(&i);

    if (checkLiterals(&i))
      if (checkSymbols(&i))
        if (checkOperations(&i))
          checkKeywords(&i);

    // std::cout << code[i] << std::endl;
  }

  return 0;
}
