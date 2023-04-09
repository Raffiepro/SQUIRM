#include "types.h"
#include "_base.h"

#include <iostream>

void Base::DefInt(WyrmAPI::Data *d) { std::cout << d->num << std::endl; }

void Base::DefString(WyrmAPI::Data *d) {
  char *c = (char *)d->data;
  for (int i = 0; i < d->num; i++)
    std::cout << c[i];
  std::cout << std::endl;
}
