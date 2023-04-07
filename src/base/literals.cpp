#include "literals.h"

#include "string.h"

WyrmAPI::Literal Base::GIntLit() {

  return WyrmAPI::Literal("Integer", [](char *c) -> WyrmAPI::LexerInfo {
    std::string num = "";

    int i = 0;
    while (c[i] >= '0' && c[i] <= '9') {
      num += c[i];
      i++;
    }

    return WyrmAPI::LexerInfo(num, i, true);
  });
}
