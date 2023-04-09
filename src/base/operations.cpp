#include "operations.h"

#include <iostream>

void Base::OIntAdd(WyrmAPI::Data *a, WyrmAPI::Data *b, WyrmAPI::Data *res) {
  std::cout << "Operado!!! " << a->num << " + " << b->num << " = "
            << a->num + b->num << std::endl;
  res->num = a->num + b->num;
}
