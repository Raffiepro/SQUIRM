#include "flags.h"

constexpr unsigned int str2int(const char *str, int h = 0) {
  return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

Wyrm::RunInfo Wyrm::GetRunInfo(int argc, char *argv[]) {

  // Crear vector de args
  std::vector<std::string> args;
  for (int i = 1; i < argc; i++) {
    args.push_back(std::string(argv[i]));
  }

  RunInfo info;

  std::vector<std::string> files;

  for (int i = 0; i < args.size(); i++) {
    switch (str2int(args[i].c_str())) {
    case str2int("-r"):
      i += 1;
      info.runnerName = args[i];
      break;
    case str2int("-d"):
      info.debug = true;
      break;
    default:
      info.files.push_back(args[i]);
      break;
    }
  }

  return info;
}
