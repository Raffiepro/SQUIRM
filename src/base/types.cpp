#include "types.h"
#include "_base.h"

WyrmAPI::Type Base::GInt() {
  WyrmAPI::Type integer;
  integer.cname = "int";
  integer.name = "int";
  integer.displayName = "Integer";
  integer.extended = false;
  integer.neutral = WyrmAPI::Data(0);
  return integer;
}
