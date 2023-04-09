#pragma once

#include <iostream>
#include "kernel.h"

namespace Wyrm {
    class Shell {
        public:
            Shell();
            ~Shell();
            static void CreateShell(Kernel *kernel);
    };
}
