#pragma once

#include <map>
#include <string>
#include <vector>

// Aixo per si volem posar mes flags al començar l'execució suposo nose
namespace Wyrm {
struct RunInfo {
  std::string runnerName = "";
  std::vector<std::string> files;
  bool debug = false;
};

RunInfo GetRunInfo(int argc, char *argv[]);
} // namespace Wyrm
