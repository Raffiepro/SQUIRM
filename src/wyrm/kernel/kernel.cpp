#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>

#include "../compiler/lexer.h"
#include "../compiler/parser.h"
#include "../compiler/serializer.h"
#include "../flags/flags.h"
#include "../version.h"
#include "kernel.h"
#include "library.h"

using namespace Wyrm;

Kernel::Kernel(RunInfo flags) { /* Constructor */
  this->flags = flags;

  this->book = new Book(flags);
  book->RegisterLibraries();
}

Kernel::~Kernel() { /* Destructor */
}

void Kernel::RunScript(std::string name) {
  std::fstream file(name);

  std::string code = "", line;
  while (std::getline(file, line)) {
    code += line + "\n";
  }

  if (flags.debug) {
    std::cout << termcolor::color<0, 150, 255> << code << termcolor::reset
              << std::endl;
  }

  Wyrm::Lexer lexer((char *)code.data(), code.size(), book);

  lexer.GenerateTokens();
  std::vector<Token> tokens = *(lexer.GetTokens());

  if (flags.debug) {
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

  Parser parser(book, tokens);

  Node *ast = parser.GetAST();

  if (flags.debug) {
    std::cout << termcolor::red << termcolor::bold << "AST:" << termcolor::reset
              << std::endl;
    ast->Debug();
    std::cout << std::endl;
  }

  // I ara aqui hem de carregar un assembler
  // Pero si no n'hi ha doncs serialitzem i tal

  WyrmAPI::TreeCode codeInfo(ast);
  if (flags.runnerName == "") {
    // Default runner
    Serializer ser(book);

    ser.SerializeToFile(codeInfo, "a.wy");
  } else {
    // Pillem el primer (falta mirar les flags)
    /*
    for (int i = 0; i < book->runners.size(); i++) {
      if (book->runners[i].GetInfo().name == flags.runnerName) {
        book->runners[i].Run(&codeInfo);
        break;
      }
    }
    */

    std::cerr << "Error: No runner with name " << flags.runnerName << std::endl;
  }
}

void Kernel::PrintVersion() {
  printVersion();

  /*
    std::cout << termcolor::bold << "Loaded "
              << termcolor::color<83, 224, 81> << book->runners.size()
              << termcolor::reset << termcolor::bold << " runners" << std::endl;
  */
  std::cout << termcolor::bold << "Loaded "
            << termcolor::color<83, 224, 81> << book->libraries.size()
            << termcolor::reset << termcolor::bold << " extension";
  if (book->libraries.size() != 1)
    std::cout << "s";
  std::cout << ":" << termcolor::reset << std::endl;

  for (int i = 0; i < book->libraries.size(); i++) {
    std::cout << "- " << termcolor::color<81, 143, 224> << termcolor::bold
              << book->libraries[i].name << termcolor::reset << ": "
              << book->libraries[i].desc << std::endl;
  }
}
