#include "version.h"
#include "_base.h"
#include "version-g.h"

#include <iostream>

int printVersion() {
  std::cout << termcolor::color<255, 168, 46> << termcolor::bold << "Wyrm"
            << termcolor::reset << " interpreter version "
            << termcolor::color<255, 255, 0> << VERSION << termcolor::reset
            << " --- (c) Aran Roig " << termcolor::reset << std::endl;
  return 0;
}
