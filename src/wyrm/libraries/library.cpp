#include "library.h"

#include <dlfcn.h>
#include <filesystem>
#include <iostream>

That::Book::Book() {}

void That::Book::RegisterLibraries() {
  // Carreguem les llibreries
  std::filesystem::path p =
      std::filesystem::canonical("/proc/self/exe").parent_path() /
      std::filesystem::path("libs/");

  for (const auto &dirEntry :
       std::filesystem::recursive_directory_iterator(p)) {
    void *handle = dlopen(dirEntry.path().c_str(), RTLD_LAZY);
    if (!handle) {
      std::cerr << "Error obrint llibreria" << std::endl;
      exit(1);
    }

    auto loadLibFunc = (WyrmAPI::Library(*)(void))dlsym(handle, "Load");
    WyrmAPI::Library l = loadLibFunc();

    std::cout << "Carregada llibreria amb nom: " << l.GetLibraryName()
              << std::endl;
    std::cout << l.GetLibraryDesc() << std::endl;

    std::vector<WyrmAPI::Type> types = l.GetTypeList();
    for (int i = 0; i < types.size(); i++) {
      this->types.push_back(types[i]);
    }

    std::vector<WyrmAPI::Operation> operations = l.GetOperationList();
    for (int i = 0; i < operations.size(); i++) {
      this->operations.push_back(operations[i]);
      this->operations[this->operations.size() - 1].SetOperationId(
          this->operations.size() - 1);
    }
  }

  /*
  void* handle = dlopen(p.c_str(), RTLD_LAZY);
  if(!handle){
      std::cerr << "Miau " << p.c_str() << std::endl;
      exit(1);
  }
  auto func = ( void*(*)(void) ) dlsym(handle, "test_funcion");
  func();
  */
}

int That::Book::GetTypeFromName(std::string name) {
  for (int i = 0; i < types.size(); i++) {
    if (types[i].name == name)
      return i;
  }
  return -1; // Error
}
