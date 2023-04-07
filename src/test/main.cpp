/* That test library 

Aquesta llibreria serveix com a exemple per integrar en That

*/

#include <iostream>
#include "../api/wyrm.h"

extern "C" {
    WyrmAPI::Library Load(){
        WyrmAPI::Library l("my_library", "My small library for Wyrm");

        return l;
    }
}