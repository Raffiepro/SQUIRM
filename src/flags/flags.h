#pragma once

#ifndef THAT_FLAGS_
#define THAT_FLAGS_

#include <string>
#include <vector>
#include <map>

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

// Aixo per si volem posar mes flags al començar l'execució suposo nose
namespace That {
    namespace Flag {
        enum Flags {
            RUN = 0,
            ASSEMBLY = 1, // Genera .th, assembly del vm
            DEBUG = 1 << 1, // Cosa de debug
            COMPILE = 1 << 2, // Genera codi en C++ i compila un binari
        };

        struct RunInfo {
            std::vector<std::string> files;
            Flags flags;
        };

        RunInfo GetRunInfo(std::vector<std::string> args);
    }
}

#endif