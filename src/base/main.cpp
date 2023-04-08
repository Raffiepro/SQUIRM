#include <iostream>

#include "../api/wyrm.h"
#include "main.h"

#include "literals.h"
#include "main.h"
#include "operations.h"
#include "types.h"

WyrmAPI::LoadInfo Library::PreLoad() {
  std::cout << "Hola" << std::endl;
  WyrmAPI::LoadInfo info;
  info.name = "Base";
  info.desc = "Base library for Wyrm";

  return info;
}

void Library::Load() {
  RegisterType(Base::GInt());

  RegisterOperation(WyrmAPI::OpSymbol::OP_ADD, WyrmAPI::OpType::OP_BINARY,
                    "Integer", "OIntAdd");

  RegisterLiteral("Integer", "GIntLit");
}

extern "C" Library *CreateLib() { return new Library; }
extern "C" void DestroyLib(Library *lib) { delete lib; }

/*
extern "C" {
WyrmAPI::Library Load() {
  WyrmAPI::Library l("base", "Base library of Wyrm");

  l.RegisterType(Base::GInt());

  l.RegisterOperation(Base::GIntAdd());

  l.RegisterLiteral(Base::GIntLit());

  return l;
}
}
*/
