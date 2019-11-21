#include <iostream>
#include <string>
#include "SmartString.h"

int main(){
    SmartString ss(new std::string("Hello"));
    std::cout << "String length: " << ss->length() << std::endl;

    if(ss->find("world") != std::string::npos){
        std::cout << "The 'ss' string does contain 'world'" << std::endl;
    } else {
        std::cout << "The 'ss' string does NOT containt 'world'" << std::endl;
    }

    std::cout << "String get test: " << *ss.get() << std::endl;

    //SmartString ss2 = ss; gives error
}
