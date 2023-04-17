#include <iostream>

#include "_base.h"
#include "main.h"

#include "literals.h"
#include "main.h"
#include "operations.h"
#include "types.h"

WyrmAPI::LoadInfo Library::PreLoad() {
  WyrmAPI::LoadInfo info;
  info.name = "Base";
  info.desc = "Base library for Wyrm";
  // Aquí s'haurien de posar dependencies suposo
  return info;
}

void Library::Load() {
  // Registrem tipus! Només necessitem el seu nom i com es declaren a C, i a
  // Wyrm, quin es el valor neutral, i també si són extesos o poden ser ints

  RegisterType("Integer", "int", false, WyrmAPI::Data(0, NULL), "DefInt");
  RegisterType("String", "string", true, WyrmAPI::Data(0, NULL), "DefString");

  // Per registrar operacions necessitem primer donar quin simbol s'utilitza,
  // després quin tipus és l'operació (binària o unitaria) i després
  // hem de passar per quin tipus és l'operació i finalment el nom de la funció
  // externa
  RegisterOperation(WyrmAPI::OpSymbol::OP_ADD, WyrmAPI::OpType::OP_BINARY,
                    "Integer", "Integer", "OIntAdd");

  // Per registrar literals primer es dona el nom del literal (per
  // identificar-lo res més), després el nom de la politica per identificar el
  // literal a partir del codi, i finalment un nom per passar aquesta part de
  // codi a un struct propi, que després es torna a reinterpretar al fer les
  // operacions.
  //
  // Tots els literals estàn obligats a tenir una operació de comparació
  RegisterLiteral("Integer", "PInt", "DInt", "CInt");
  RegisterLiteral("String", "PString", "DString", "CString");
}

extern "C" Library *CreateLib() { return new Library; }
extern "C" void DestroyLib(Library *lib) { delete lib; }
