#pragma once

#include "../_base.h"
#include "../kernel/library.h"

#include <filesystem>
#include <string>
#include <vector>

namespace Wyrm {
class Serializer {
public:
  Serializer(Book *book);

  std::filesystem::path GetExecPath();
  void SerializeToFile(WyrmAPI::TreeCode codeInfo, std::string fileName);
  std::string SerialzeToString(WyrmAPI::TreeCode codeInfo);
  void SerializeString(FILE *f, std::string s);
  void SerializeAtom(FILE *f, WyrmAPI::Atom *atom);
  void SerializeNode(FILE *f, WyrmAPI::Node *n, std::vector<std::string> &libs);

  std::string ReadString(FILE *f);
  WyrmAPI::Node *ReadNode(FILE *f);
  WyrmAPI::TreeCode LoadFromFile(std::string fileName);

private:
  Book *book;
};
} // namespace Wyrm
