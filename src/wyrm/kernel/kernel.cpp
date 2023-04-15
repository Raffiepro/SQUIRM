#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>

#include <gmp.h>

#include "../compiler/lexer.h"
#include "../compiler/parser.h"
#include "../flags/flags.h"
#include "../version.h"
#include "kernel.h"
#include "library.h"

using namespace Wyrm;

Kernel::Kernel() { /* Constructor */
}

Kernel::~Kernel() { /* Destructor */
}

void Kernel::DebugTokens(std::vector<Wyrm::Token> tokens) {
  std::cout << termcolor::red << termcolor::bold
            << "Tokens:" << termcolor::reset << std::endl;
  std::map<TokenType, std::string> mapo = {
      {TokenType::ERROR, "ERROR"},
      {TokenType::SEPARATOR, "SEPARATOR"},
      {TokenType::TYPE, "TYPE"},
      {TokenType::ADD, "ADD"},             // +            X
      {TokenType::SUBTRACT, "SUBTRACT"},   // -            X
      {TokenType::MULTIPLY, "MULTIPLY"},   // *            X
      {TokenType::DIVIDE, "DIVIDE"},       // /            X
      {TokenType::MODULO, "MODULO"},       // %            X
      {TokenType::INCREMENT, "INCREMENT"}, // ++           X
      {TokenType::DECREMENT, "DECREMENT"}, // --           X
      {TokenType::NOT, "NOT"},             // !
      {TokenType::AND, "AND"},
      {TokenType::OR, "OR"},
      {TokenType::EQUAL, "EQUAL"},                             // ==           X
      {TokenType::GREATER_THAN, "GREATER_THAN"},               // >            X
      {TokenType::LESSER_THAN, "LESSER_THAN"},                 // <            X
      {TokenType::GREATER_EQUAL_THAN, "GREATER_EQUAL_THAN"},   // >= X
      {TokenType::LESSER_EQUAL_THAN, "LESSER_EQUAL_THAN"},     // <= X
      {TokenType::NOT_EQUAL, "NOT_EQUAL"},                     // !=           X
      {TokenType::ASSIGMENT, "ASSIGMENT"},                     // =            X
      {TokenType::ASSIGMENT_ADD, "ASSIGMENT_ADD"},             // +=           X
      {TokenType::ASSIGMENT_SUBTRACT, "ASSIGMENT_SUBTRACT"},   // -= X
      {TokenType::ASSIGMENT_MULTIPLY, "ASSIGMENT_MULTIPLY"},   // *= X
      {TokenType::ASSIGMENT_DIVIDE, "ASSIGMENT_DIVIDE"},       // /= X
      {TokenType::ASSIGMENT_MODULO, "ASSIGMENT_MODULO"},       // %= X
      {TokenType::COMMA, "COMMA"},                             // ,        X
      {TokenType::POINT, "POINT"},                             // .        X
      {TokenType::PARENTHESIS_OPEN, "PARENTHESIS_OPEN"},       // (        X
      {TokenType::PARENTHESIS_CLOSE, "PARENTHESIS_CLOSE"},     // ) X
      {TokenType::SQUARE_BRACKET_OPEN, "SQUARE_BRACKET_OPEN"}, // [ X
      {TokenType::SQUARE_BRACKET_CLOSE, "SQUARE_BRACKET_CLOSE"}, // ] X
      {TokenType::CURLY_BRACKET_OPEN, "CURLY_OPEN"},             // {        X
      {TokenType::CURLY_BRACKET_CLOSE, "CURLY_CLOSE"},           // }        X
      {TokenType::DOLLAR, "DOLLAR"},                             // $
      {TokenType::SEMICOLON, "SEMICOLON"},                       // ;        X
      {TokenType::TWO_POINTS, "TWO_POINTS"},                     // :        X
      {TokenType::ARROW_RIGHT, "ARROW_RIGHT"},                   // ->
      {TokenType::IF, "IF"},                                     // if        X
      {TokenType::ELSE, "ELSE"},                                 // else      X
      {TokenType::WHILE, "WHILE"},                               // while     X
      {TokenType::RETURN, "RETURN"},                             // return    X
      {TokenType::BREAK, "BREAK"},                               // stop      X
      {TokenType::CONTINUE, "CONTINUE"},                         // skip      X
      {TokenType::FOR, "FOR"},
      {TokenType::LITERAL, "LITERAL"},           // 3        X
      {TokenType::FUNCTION_DECLARATION, "FUNC"}, // func     X
      {TokenType::MODULE_DECLARATION, "USE"},    // use      X
      {TokenType::IMPORT_DECLARATION, "IMPORT"}, // import   X
      {TokenType::IDENTIFIER, "ID"}              //  algo     X
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

  

  // I ara aqui hem de carregar un assembler
  /*
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
  */
}

void Kernel::PrintVersion() { printVersion(); }
