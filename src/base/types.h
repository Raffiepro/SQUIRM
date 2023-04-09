#pragma once

#include "../api/wyrm.h"

#include "operations.h"

extern "C" namespace Base {
  void DefInt(WyrmAPI::Data * d);
  void DefString(WyrmAPI::Data * d);
}
