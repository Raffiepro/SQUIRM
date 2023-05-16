#include <iostream>

#include "_base.h"
#include "main.h"

WyrmAPI::LoadInfo Amph::PreLoad() {
  WyrmAPI::LoadInfo info;
  info.name = "Amph";
  info.desc = "Official Wyrm interpreter";

  info.isRunner = true;
  info.runnerName = "amph";

  return info;
}

void Amph::Load() {
  
}

extern "C" void Run(Node* ast){
    std::cout << "Ahora aqui se runean las cosas" << std::endl;
}

extern "C" Amph *CreateLib() { return new Amph; }
extern "C" void DestroyLib(Amph *lib) { delete lib; }
