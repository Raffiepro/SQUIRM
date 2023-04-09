#include "literals.h"

#include "string.h"
#include <iostream>

WyrmAPI::LexerInfo *Base::PInt(char *c, int end) {
  std::string num = "";

  int i = 0;
  while (c[i] >= '0' && c[i] <= '9' && i < end) {
    num += c[i];
    i++;
  }

  if (i > 0)
    return new WyrmAPI::LexerInfo(true, num, i);
  return new WyrmAPI::LexerInfo(false);
}

WyrmAPI::LexerInfo *Base::PString(char *c, int end) {
  std::string s = "";
  int i = 0;
  if (c[i] == '\"') {
    i++;
    while (i < end) {
      if (c[i] == '\"') {
        break;
      }
      s += c[i];
      i++;
    }
    i++;

    return new WyrmAPI::LexerInfo(true, s, i);
  }
  return new WyrmAPI::LexerInfo(false);
}

WyrmAPI::Data *Base::DInt(std::string s) {
  WyrmAPI::Data *res = new WyrmAPI::Data();
  res->num = std::stoi(s);
  return res;
}

WyrmAPI::Data *Base::DString(std::string s) {
  WyrmAPI::Data *res = new WyrmAPI::Data();
  res->num = s.size();
  char *c = (char *)s.c_str();
  res->data = (void *)c;
  return res;
}
