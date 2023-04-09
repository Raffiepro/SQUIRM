#pragma once

#include "_base.h"

extern "C" namespace Base {
  WyrmAPI::LexerInfo *PInt(char *c, int end);
  WyrmAPI::LexerInfo *PString(char *c, int end);

  WyrmAPI::Data *DInt(std::string s);
  WyrmAPI::Data *DString(std::string s);

  bool CInt(WyrmAPI::Data * a, WyrmAPI::Data * b);
  bool CString(WyrmAPI::Data * a, WyrmAPI::Data * b);
}
