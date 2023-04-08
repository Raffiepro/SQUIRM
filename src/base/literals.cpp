#include "literals.h"

#include "string.h"
#include <iostream>

WyrmAPI::LexerInfo *Base::GIntLit(char *c) {
  std::string num = "";

  int i = 0;
  while (c[i] >= '0' && c[i] <= '9') {
    num += c[i];
    i++;
  }

  if (i > 0)
    return new WyrmAPI::LexerInfo(true, num, i);
  return new WyrmAPI::LexerInfo(false);
}
