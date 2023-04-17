#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>

#include <gmp.h>

#include "../compiler/lexer.h"
#include "../compiler/parser.h"
#include "../compiler/serializer.h"
#include "../flags/flags.h"
#include "../version.h"
#include "kernel.h"
#include "library.h"

using namespace Wyrm;

Kernel::Kernel() { /* Constructor */
}

Kernel::~Kernel() { /* Destructor */
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

  Wyrm::Lexer lexer((char *) code.data(), code.size(), &book);

  lexer.GenerateTokens();
  std::vector<Token> tokens = *(lexer.GetTokens());

  if (CHECK_BIT(flags, 1)) {
    WyrmAPI::DebugTokens(tokens);
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
  // Pero si no n'hi ha doncs serialitzem i tal

  Serializer ser(&book);

  WyrmAPI::TreeCode codeInfo(ast);

  std::cout << "hola" << std::endl;
  ser.SerializeToFile(codeInfo, "a.wy");
  
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
