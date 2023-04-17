#pragma once

#include "../_base.h"
#include "../flags/flags.h"
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

  bool (*compLit)(WyrmAPI::Data *, WyrmAPI::Data *);

  Literal(std::string name, WyrmAPI::LexerInfo *(*policy)(char *, int),
          WyrmAPI::Data *(*toData)(std::string r),
          bool (*compLit)(WyrmAPI::Data *, WyrmAPI::Data *)) {
    this->name = name;
    this->policy = policy;
    this->toData = toData;
    this->compLit = compLit;
  }
};

struct Type {
  std::string name;
  std::string wname;
  bool extended;
  WyrmAPI::Data neutral;
  void (*defFunction)(WyrmAPI::Data *);

  Type(std::string name, std::string wname, bool extended,
       WyrmAPI::Data neutral, void (*defFunction)(WyrmAPI::Data *)) {
    this->name = name;
    this->wname = wname;
    this->extended = extended;
    this->neutral = neutral;
    this->defFunction = defFunction;
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

class InternalRunner {
public:
  InternalRunner() {}
  InternalRunner(int (*compFunc)(WyrmAPI::TreeCode *),
                 WyrmAPI::RunnerInfo info) {
    this->compFunc = compFunc;
    this->info = info;
  };

  int Run(WyrmAPI::TreeCode *n) { return this->compFunc(n); }

  WyrmAPI::RunnerInfo GetInfo() { return info; }

private:
  int (*compFunc)(WyrmAPI::TreeCode *);
  WyrmAPI::RunnerInfo info;
};

class Book {
  // std::vector<WyrmAPI::Library> libs;
public:
  std::vector<Type> types;
  std::vector<Operation> operations;
  std::vector<Literal> literals;

  std::vector<InternalRunner> runners;

  Book(Flag::Flags flags);
  Book();

  void RegisterLibraries();
  int GetTypeFromName(std::string name);

private:
  Flag::Flags flags;
};
} // namespace Wyrm
