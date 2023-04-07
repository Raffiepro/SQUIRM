#include <iostream>

#include "../api/wyrm.h"

#include "literals.h"
#include "operations.h"
#include "types.h"

extern "C" {
WyrmAPI::Library Load() {
  WyrmAPI::Library l("base", "Base library of Wyrm");

  l.RegisterType(Base::GInt());

  l.RegisterOperation(Base::GIntAdd());

  l.RegisterLiteral(Base::GIntLit());

  return l;
}
}
