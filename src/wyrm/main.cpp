#include <iostream>
#include <string>
#include <vector>

#include "kernel/kernel.h"

using namespace Wyrm;

int Run(RunInfo runInfo);

int main(int argc, char *argv[]) {
  RunInfo runInfo = GetRunInfo(argc, argv);

  return Run(runInfo);
}

int Run(RunInfo runInfo) {
  
  Wyrm::Kernel kernel(runInfo);

  if (runInfo.files.size() == 0) {
    kernel.PrintVersion();
    // kernel.Cli();
    return 0;
  }

  kernel.RunScript(runInfo.files[0]);

  return 0;
}
