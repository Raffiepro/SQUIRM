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

  Book book(flags);
  book.RegisterLibraries();

  std::string code = "", line;
  while (std::getline(file, line)) {
    code += line + "\n";
  }
  if (CHECK_BIT(flags, 1)) {
    std::cout << termcolor::color<0, 150, 255> << code << termcolor::reset
              << std::endl;
  }

  Wyrm::Lexer lexer((char *)code.data(), code.size(), &book);

  lexer.GenerateTokens();
  std::vector<Token> tokens = *(lexer.GetTokens());

  if (CHECK_BIT(flags, 1)) {
    std::cout << termcolor::red << termcolor::bold
              << "TOKENS:" << termcolor::reset << std::endl;
    for (int i = 0; i < tokens.size(); i++) {
      std::cout << "[";
      std::cout << "type: " << termcolor::green;
      tokens[i].Debug();
      std::cout << termcolor::reset;
      if (tokens[i].value.size() > 0) {
        std::cout << ", value: " << termcolor::yellow << tokens[i].value
                  << termcolor::reset << "]";
      } else {
        std::cout << "]";
      }
      if (i < tokens.size() - 1)
        std::cout << ", ";
    }
    std::cout << std::endl;
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

  WyrmAPI::TreeCode codeInfo(ast);
  if (book.runners.size() == 0) {
    // Default runner
    Serializer ser(&book);

    ser.SerializeToFile(codeInfo, "a.wy");
  } else {
    // Pillem el primer (falta mirar les flags)
    book.runners[0].Run(&codeInfo);
  }
}

void Kernel::PrintVersion() { printVersion(); }
