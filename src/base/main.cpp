#include <iostream>

#include "../api/wyrm.h"

#include "literals.h"
#include "operations.h"
#include "types.h"

// Aqui posem algunes funcions
void IntegerAdd(ThatAPI::Data *a, ThatAPI::Data *b, ThatAPI::Data *res) {
  std::cout << "Testeando" << std::endl;
}

extern "C++" {
ThatAPI::Library Load() {
  ThatAPI::Library l("base", "Base library of Wyrm");

  l.RegisterType(Base::GInt());

  l.RegisterOperation(Base::GIntAdd());

  l.RegisterLiteral(Base::GIntLit());

  return l;
}
}
