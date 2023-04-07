#include "operations.h"

#include <iostream>

WyrmAPI::Operation Base::GIntAdd() {
  WyrmAPI::Operation integerAdd;

  integerAdd.operationType = WyrmAPI::OpType::OP_BINARY;
  integerAdd.simbol = WyrmAPI::OpSymbol::OP_ADD;
  integerAdd.elementType = "Integer";
  integerAdd.binaryOperation = Base::OIntAdd;

  return integerAdd;
}

void Base::OIntAdd(WyrmAPI::Data *a, WyrmAPI::Data *b, WyrmAPI::Data *res) {
  std::cout << "Testeando" << std::endl;
}
