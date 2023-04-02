#include "library.h"

#include <filesystem>
#include <iostream>
#include <dlfcn.h>

That::Book::Book(){
    // Carreguem les llibreries
    std::filesystem::path p = std::filesystem::canonical("/proc/self/exe").parent_path() / std::filesystem::path("libs/");

    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(p)){
        void* handle = dlopen(dirEntry.path().c_str(), RTLD_LAZY);
        if(!handle){
            std::cerr << "Error obrint llibreria" << std::endl;
            exit(1);
        }

        auto loadLibFunc = ( ThatAPI::Library(*)(void) ) dlsym(handle, "Load");
        ThatAPI::Library l = loadLibFunc();

        std::cout << "Carregada llibreria amb nom: " << l.GetLibraryName() << std::endl;

        libs.push_back(l);
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