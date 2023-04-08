#include "types.h"
#include "_base.h"

WyrmAPI::Type *Base::GInt() {
  WyrmAPI::Type *integer = new WyrmAPI::Type();
  integer->cname = "int";
  integer->wname = "int";
  integer->name = "Integer";
  integer->extended = false;
  integer->neutral = WyrmAPI::Data(0);
  return integer;
}
