#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>

#include <gmp.h>

#include "../compiler/lexer.h"
#include "../compiler/parser.h"
#include "../flags/flags.h"
#include "../version.h"
#include "../vm/machine.h"
#include "kernel.h"
#include "library.h"
#include "shell.h"

using namespace Wyrm;

Kernel::Kernel() { /* Constructor */
}

Kernel::~Kernel() { /* Destructor */
}

void Kernel::DebugTokens(std::vector<Wyrm::Token> tokens) {
  std::cout << termcolor::red << termcolor::bold
            << "Tokens:" << termcolor::reset << std::endl;
  std::map<WyrmAPI::TokenType, std::string> mapo = {
      {WyrmAPI::TokenType::ERROR, "ERROR"},
      {WyrmAPI::TokenType::SEPARATOR, "SEPARATOR"},
      {WyrmAPI::TokenType::TYPE, "TYPE"},
      {WyrmAPI::TokenType::ADD, "ADD"},             // +            X
      {WyrmAPI::TokenType::SUBTRACT, "SUBTRACT"},   // -            X
      {WyrmAPI::TokenType::MULTIPLY, "MULTIPLY"},   // *            X
      {WyrmAPI::TokenType::DIVIDE, "DIVIDE"},       // /            X
      {WyrmAPI::TokenType::MODULO, "MODULO"},       // %            X
      {WyrmAPI::TokenType::INCREMENT, "INCREMENT"}, // ++           X
      {WyrmAPI::TokenType::DECREMENT, "DECREMENT"}, // --           X
      {WyrmAPI::TokenType::NOT, "NOT"},             // !
      {WyrmAPI::TokenType::AND, "AND"},
      {WyrmAPI::TokenType::OR, "OR"},
      {WyrmAPI::TokenType::EQUAL, "EQUAL"},               // ==           X
      {WyrmAPI::TokenType::GREATER_THAN, "GREATER_THAN"}, // >            X
      {WyrmAPI::TokenType::LESSER_THAN, "LESSER_THAN"},   // <            X
      {WyrmAPI::TokenType::GREATER_EQUAL_THAN, "GREATER_EQUAL_THAN"}, // >= X
      {WyrmAPI::TokenType::LESSER_EQUAL_THAN, "LESSER_EQUAL_THAN"},   // <= X
      {WyrmAPI::TokenType::NOT_EQUAL, "NOT_EQUAL"},         // !=           X
      {WyrmAPI::TokenType::ASSIGMENT, "ASSIGMENT"},         // =            X
      {WyrmAPI::TokenType::ASSIGMENT_ADD, "ASSIGMENT_ADD"}, // +=           X
      {WyrmAPI::TokenType::ASSIGMENT_SUBTRACT, "ASSIGMENT_SUBTRACT"}, // -= X
      {WyrmAPI::TokenType::ASSIGMENT_MULTIPLY, "ASSIGMENT_MULTIPLY"}, // *= X
      {WyrmAPI::TokenType::ASSIGMENT_DIVIDE, "ASSIGMENT_DIVIDE"},     // /= X
      {WyrmAPI::TokenType::ASSIGMENT_MODULO, "ASSIGMENT_MODULO"},     // %= X
      {WyrmAPI::TokenType::COMMA, "COMMA"},                       // ,        X
      {WyrmAPI::TokenType::POINT, "POINT"},                       // .        X
      {WyrmAPI::TokenType::PARENTHESIS_OPEN, "PARENTHESIS_OPEN"}, // (        X
      {WyrmAPI::TokenType::PARENTHESIS_CLOSE, "PARENTHESIS_CLOSE"},       // ) X
      {WyrmAPI::TokenType::SQUARE_BRACKET_OPEN, "SQUARE_BRACKET_OPEN"},   // [ X
      {WyrmAPI::TokenType::SQUARE_BRACKET_CLOSE, "SQUARE_BRACKET_CLOSE"}, // ] X
      {WyrmAPI::TokenType::CURLY_BRACKET_OPEN, "CURLY_OPEN"},   // {        X
      {WyrmAPI::TokenType::CURLY_BRACKET_CLOSE, "CURLY_CLOSE"}, // }        X
      {WyrmAPI::TokenType::DOLLAR, "DOLLAR"},                   // $
      {WyrmAPI::TokenType::SEMICOLON, "SEMICOLON"},             // ;        X
      {WyrmAPI::TokenType::TWO_POINTS, "TWO_POINTS"},           // :        X
      {WyrmAPI::TokenType::ARROW_RIGHT, "ARROW_RIGHT"},         // ->
      {WyrmAPI::TokenType::IF, "IF"},                           // if        X
      {WyrmAPI::TokenType::ELSE, "ELSE"},                       // else      X
      {WyrmAPI::TokenType::WHILE, "WHILE"},                     // while     X
      {WyrmAPI::TokenType::RETURN, "RETURN"},                   // return    X
      {WyrmAPI::TokenType::BREAK, "BREAK"},                     // stop      X
      {WyrmAPI::TokenType::CONTINUE, "CONTINUE"},               // skip      X
      {WyrmAPI::TokenType::FOR, "FOR"},
      {WyrmAPI::TokenType::LITERAL, "LITERAL"},           // 3        X
      {WyrmAPI::TokenType::FUNCTION_DECLARATION, "FUNC"}, // func     X
      {WyrmAPI::TokenType::MODULE_DECLARATION, "USE"},    // use      X
      {WyrmAPI::TokenType::IMPORT_DECLARATION, "IMPORT"}, // import   X
      {WyrmAPI::TokenType::IDENTIFIER, "ID"}              //  algo     X
  };

  for (int i = 0; i < tokens.size(); i++) {
    std::cout << "[";
    std::cout << "type: " << mapo[tokens[i].type];
    if (tokens[i].value.size() > 0) {
      std::cout << ", value: " << tokens[i].value << "]";
    } else {
      std::cout << "]";
    }
    if (i < tokens.size() - 1)
      std::cout << ", ";
  }
  std::cout << std::endl;
}

void Kernel::RunScript(std::string name, Flag::Flags flags) {
  std::fstream file(name);

  Book book;
  book.RegisterLibraries();

  std::string code = "", line;
  while (std::getline(file, line)) {
    code += line + "\n";
  }
  if (CHECK_BIT(flags, 1)) {
    std::cout << termcolor::color<0, 150, 255> << code << termcolor::reset
              << std::endl;
  }

  Wyrm::Lexer lexer(code.data(), code.size(), &book);

  lexer.GenerateTokens();
  std::vector<Token> tokens = *(lexer.GetTokens());

  if (CHECK_BIT(flags, 1)) {
    DebugTokens(tokens);
  }

  Parser parser(&book, tokens);

  Node *ast = parser.GetAST();

  if (CHECK_BIT(flags, 1)) {
    std::cout << termcolor::red << termcolor::bold << "AST:" << termcolor::reset
              << std::endl;
    ast->Debug();
    std::cout << std::endl;
  }

  Assembler assembler(&book, ast);

  if (CHECK_BIT(flags, 2)) {
    // Compilem a C++
    // std::cout << termcolor::color<255,122,0> << "Compiling..." << std::endl;
    Reinterpreter reinterpreter;
    Builder::BuildCode(reinterpreter.GetCode(ast), Builder::GetExeName(name));

  } else {
    // Interpretem
    MachineCode machineCode = assembler.GetAssembly();

    if (CHECK_BIT(flags, 1)) {
      std::cout << termcolor::red << termcolor::bold
                << "ASM:" << termcolor::reset << std::endl;
      // Ara doncs fem debug de les instruccions
      std::map<InstructionID, std::string> ins = {
          {LOADC, "LOADC"},   {MOVE, "MOVE"},   {CALL, "CALL"},
          {DEF, "DEF"},       {ICL, "ICL"},     {RET, "RET"},
          {BINARY, "BINARY"}, {UNARY, "UNARY"}, {ASSIGNARY, "ASSIGNARY"},
          {TO, "TO"},         {END, "END"},     {JUMP, "JUMP"},
          {TEST, "TEST"},     {HALT, "HALT"},
      };

      for (int i = 0; i < machineCode.instructions.size(); i++) {
        std::cout << termcolor::color<255, 125, 0> << "(" << i << ") "
                  << termcolor::reset;
        std::cout << ins[machineCode.instructions[i].type] << " ";
        // std::cout << "= " << machineCode.instructions[i].type << " ";
        if (machineCode.instructions[i].GetA() != INT32_MIN)
          std::cout << machineCode.instructions[i].GetA() << " ";
        if (machineCode.instructions[i].GetB() != INT32_MIN)
          std::cout << machineCode.instructions[i].GetB() << " ";
        if (machineCode.instructions[i].GetC() != INT32_MIN)
          std::cout << machineCode.instructions[i].GetC() << " ";
        std::cout << std::endl;
      }
      std::cout << std::endl;
    }
    // exit(1);
    VM machine(&book, flags);
    // TODO: Hacer esto
    if (CHECK_BIT(flags, 1)) {
      std::cout << termcolor::red << termcolor::bold
                << "EXEC:" << termcolor::reset << std::endl;
    }
    machine.Run(machineCode);
  }

  delete ast;
}

void Kernel::Cli() {
  Shell::CreateShell(this);
  return;
}

void Kernel::PrintVersion() { printVersion(); }
