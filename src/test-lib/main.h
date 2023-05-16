#pragma once

#include "_base.h"

class Library : public WyrmAPI::Library {
public:
  virtual WyrmAPI::LoadInfo PreLoad();
  virtual void Load();
};
