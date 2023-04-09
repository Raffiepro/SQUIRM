#pragma once

#include <cstdint>
#include <map>
#include <stack>
#include <unordered_map>
#include <vector>

#include "../flags/flags.h"
#include "../libraries/library.h"
#include "data.h"
#include "internal.h"

#define UINT32_SIZE 4

namespace Wyrm {
class VM {

public:
  VM(Book *book, Flag::Flags flags);
  void Run(MachineCode code);

private:
  // std::vector<reg_t> stack;
  Flag::Flags flags;
  Book *book;

  // std::stack<int> offsets;
  std::unordered_map<unsigned int, Operation> operations;

  void MemDump(uint8_t *data, int size);

  void Process(Instruction ins, int *current, std::vector<Atom> *constants,
               Atom *registers);
  void Operate(WyrmAPI::OpSymbol op, Atom *a, Atom *b, Atom *c);

  std::string GetOperationName(WyrmAPI::OpSymbol t);

  bool debug;
  unsigned int offset;

  // void RegDump(Regs* regs, int n);
};
} // namespace Wyrm
