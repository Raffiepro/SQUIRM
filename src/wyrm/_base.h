// Aquest arxiu només inclou el header de la api que es troba a fora
// malauradament
#pragma once
#include "../api/wyrm.h"
#if defined _WIN32 || defined __MINGW32__
#define WINDOWS
#else
#define LINUX
#endif
