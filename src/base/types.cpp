#include "types.h"
#include "_base.h"

ThatAPI::Type Base::GInt() {
  ThatAPI::Type integer;
  integer.cname = "int";
  integer.name = "int";
  integer.displayName = "Integer";
  integer.extended = false;
  integer.neutral = ThatAPI::Data(0);
  return integer;
}
