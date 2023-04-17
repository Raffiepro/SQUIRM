#pragma once

#include "../compiler/lexer.h"
#include "../flags/flags.h"
#include <string>
#define DEBUG

/*
En principi el Kernel és l'objecte capaç de compilar i interpretar el codi
suposo
*/
namespace Wyrm {
class Kernel {
public:
  Kernel();
  ~Kernel();

  void RunScript(std::string file, Flag::Flags flags);
  void SendByteScript(char name[]);

  void PrintVersion();

private:
  void DebugTokens(std::vector<WyrmAPI::Token> tokens);
};
} // namespace Wyrm
