/* That test library 

Aquesta llibreria serveix com a exemple per integrar en That

*/

#include <iostream>

extern "C" {
    void test_funcion(){
        std::cout << "Hola si això funciona" << std::endl;
    }
}