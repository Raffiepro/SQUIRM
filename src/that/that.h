#pragma once
// That api handler

// Aquest header comunica entre el llenguatge i la api d'aquest

#include <string>

namespace ThatAPI {
    class Library {
        std::string libraryName;
        std::string libraryDesc;

        public:
            Library(std::string name, std::string description){
                this->libraryName = name;
                this->libraryDesc = description;
            }


            std::string GetLibraryName(){
                return libraryName;
            }
    };
}
