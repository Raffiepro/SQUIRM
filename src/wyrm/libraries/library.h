#pragma once

#include "../../api/wyrm.h"
#include <dlfcn.h>

#include <filesystem>
#include <vector>

namespace Wyrm {

struct Literal { // Qualsevol cosa que no comenci amb un punt
  std::string name;
  WyrmAPI::LexerInfo *(*policy)(char *, int);
  // El que retorna es el offset del literal, el punter es a on detectar. Ha de
  // retornar -1 en cas que no s'hagi detectat res
  WyrmAPI::Data *(*toData)(std::string);

  Literal(std::string name, WyrmAPI::LexerInfo *(*policy)(char *, int),
          WyrmAPI::Data *(*toData)(std::string r)) {
    this->name = name;
    this->policy = policy;
    this->toData = toData;
  }
};

class Operation {
public:
  WyrmAPI::OpSymbol simbol;
  WyrmAPI::OpType operationType;

  std::string fromElementType;
  std::string toElementType;

  int GetOperationId() { return elementTypeId; }

  void SetOperationId(int id) { elementTypeId = id; }

  union {
    void (*binaryOperation)(WyrmAPI::Data *a, WyrmAPI::Data *b,
                            WyrmAPI::Data *res);
    void (*unaryOperation)(WyrmAPI::Data *a, WyrmAPI::Data *res);
    void (*conversion)(WyrmAPI::Data *res);
  };

private:
  int elementTypeId;
};

class Book {
  // std::vector<WyrmAPI::Library> libs;
public:
  std::vector<WyrmAPI::Type *> types;
  std::vector<Operation> operations;
  std::vector<Literal> literals;

  Book();

  void RegisterLibraries();
  int GetTypeFromName(std::string name);
};
} // namespace Wyrm
