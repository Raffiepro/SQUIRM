#include <iostream>

#include "_base.h"
#include "main.h"

WyrmAPI::LoadInfo Library::PreLoad() {
  WyrmAPI::LoadInfo info;
  info.name = "Drac";
  info.desc = "Wyrm C/C++ Transcompiler";
  
  info.isRunner = true;
  info.runnerName = "drac";

  return info;
}

void Library::Load() {
  
}

extern "C" Library *CreateLib() { return new Library; }
extern "C" void DestroyLib(Library *lib) { delete lib; }
