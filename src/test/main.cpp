/* That test library 

Aquesta llibreria serveix com a exemple per integrar en That

*/

#include <iostream>
#include "../api/wyrm.h"

extern "C" {
    ThatAPI::Library Load(){
        ThatAPI::Library l("my_library", "My small library for Wyrm");

        return l;
    }
}