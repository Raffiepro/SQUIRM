#pragma once

#include "_base.h"

using namespace WyrmAPI;

class Amph : public Library {
public:
  virtual LoadInfo PreLoad();
  virtual void Load();
};
