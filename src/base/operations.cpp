#include "operations.h"

#include <iostream>

ThatAPI::Operation Base::GIntAdd() {
  ThatAPI::Operation integerAdd;

  integerAdd.operationType = ThatAPI::OpType::OP_BINARY;
  integerAdd.simbol = ThatAPI::OpSymbol::OP_ADD;
  integerAdd.elementType = "Integer";
  integerAdd.binaryOperation = Base::OIntAdd;

  return integerAdd;
}

void Base::OIntAdd(ThatAPI::Data *a, ThatAPI::Data *b, ThatAPI::Data *res) {
  std::cout << "Testeando" << std::endl;
}
