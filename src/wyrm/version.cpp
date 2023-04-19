#include "version.h"
#include "_base.h"
#include "version-g.h"

#include <iostream>

int printVersion() {
  std::cout << termcolor::color<227, 93, 86> << termcolor::bold << "Wyrm"
            << termcolor::color<83, 224, 81> << " " << VERSION
            << termcolor::reset << std::endl;
  return 0;
}
