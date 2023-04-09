#include "library.h"

#include <dlfcn.h>
#include <filesystem>
#include <iostream>

Wyrm::Book::Book() {}

void Wyrm::Book::RegisterLibraries() {
  // Carreguem les llibreries
  std::filesystem::path p =
      std::filesystem::canonical("/proc/self/exe").parent_path() /
      std::filesystem::path("libs/");

  for (const auto &dirEntry :
       std::filesystem::recursive_directory_iterator(p)) {

    void *handle = dlopen(dirEntry.path().c_str(), RTLD_LAZY);
    if (!handle) {
      std::cerr << "Error obrint llibreria " << dirEntry.path().c_str()
                << std::endl;
      exit(1);
    }

    WyrmAPI::Library *(*CreateLibFunc)(void) =
        (WyrmAPI::Library * (*)(void)) dlsym(handle, "CreateLib");
    void (*DestroyLibFunc)(WyrmAPI::Library *) =
        (void (*)(WyrmAPI::Library *))dlsym(handle, "DestroyLib");

    WyrmAPI::Library *l = CreateLibFunc();

    WyrmAPI::LoadInfo info = l->PreLoad();

    std::cout << info.name << " - " << info.desc << std::endl;

    l->Load();

    std::vector<WyrmAPI::Type *> types = l->_GetTypeList();
    for (int i = 0; i < types.size(); i++) {
      this->types.push_back(types[i]);
    }

    // Carreguem coses
    std::vector<std::tuple<std::string, std::string, std::string, std::string>>
        literals = l->_GetLiterals();

    for (int i = 0; i < literals.size(); i++) {
      Literal lit(std::get<0>(literals[i]),
                  (WyrmAPI::LexerInfo * (*)(char *, int))
                      dlsym(handle, std::get<1>(literals[i]).c_str()),
                  (WyrmAPI::Data * (*)(std::string))
                      dlsym(handle, std::get<2>(literals[i]).c_str()),
                  (bool (*)(WyrmAPI::Data *, WyrmAPI::Data *))dlsym(
                      handle, std::get<3>(literals[i]).c_str()));

      this->literals.push_back(lit);

      /*
      std::cout << "Hola registrat literalment" << std::endl;

      char c[] = "Hola que tal";
      lit.policy(c, 12);
      */
    }

    std::vector<std::tuple<WyrmAPI::OpSymbol, WyrmAPI::OpType, std::string,
                           std::string, std::string>>
        operations = l->_GetOperations();
    for (int i = 0; i < operations.size(); i++) {
      Operation op;
      op.simbol = std::get<0>(operations[i]);
      op.operationType = std::get<1>(operations[i]);
      op.fromElementType = std::get<2>(operations[i]);
      op.toElementType = std::get<3>(operations[i]);

      switch (op.operationType) {
      case WyrmAPI::OpType::OP_BINARY:

        op.binaryOperation =
            (void (*)(WyrmAPI::Data *, WyrmAPI::Data *, WyrmAPI::Data *))dlsym(
                handle, std::get<4>(operations[i]).c_str());
        break;
      case WyrmAPI::OpType::OP_UNARY:
        op.unaryOperation = (void (*)(WyrmAPI::Data *, WyrmAPI::Data *))dlsym(
            handle, std::get<4>(operations[i]).c_str());
        break;
      case WyrmAPI::OpType::OP_CONVERSION:
        op.conversion = (void (*)(WyrmAPI::Data *))dlsym(
            handle, std::get<4>(operations[i]).c_str());
        break;
      default:
        break;
      }

      this->operations.push_back(op);
    }

    DestroyLibFunc(l);
  }
}

int Wyrm::Book::GetTypeFromName(std::string name) {
  for (int i = 0; i < types.size(); i++) {
    if (types[i]->name == name)
      return i;
  }
  return -1; // Error
}
