#include "types.h"
#include "_base.h"

WyrmAPI::Type *Base::TInt() {
  WyrmAPI::Type *integer = new WyrmAPI::Type();
  integer->cname = "int";
  integer->cstructdef = "";
  integer->wname = "int";
  integer->name = "Integer";
  integer->extended = false;
  integer->neutral = WyrmAPI::Data(0);
  return integer;
}

WyrmAPI::Type *Base::TString() {
  WyrmAPI::Type *string = new WyrmAPI::Type();
  string->cname = "std::string";
  string->cstructdef = "";
  string->wname = "string";
  string->name = "String";
  string->extended = true;
  string->neutral = WyrmAPI::Data(0); // ""
  return string;
}
