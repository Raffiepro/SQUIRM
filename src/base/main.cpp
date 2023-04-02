#include <iostream>

#include "that.h"

extern "C" {
    ThatAPI::Library Load(){
        ThatAPI::Library l("base");
        return l;
    }
}