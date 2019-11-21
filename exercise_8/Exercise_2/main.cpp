#include <iostream>
#include <string>
#include "SmartString.h"

int main(){
    SmartString ss(new std::string("Hello")); //+1
    std::cout << "String length: " << ss->length() << std::endl;

    if(ss->find("world") != std::string::npos){
        std::cout << "The 'ss' string does contain 'world'" << std::endl;
    } else {
        std::cout << "The 'ss' string does NOT containt 'world'" << std::endl;
    }

    std::cout << "String get test for ss: " << *ss.get() << std::endl;

    SmartString ss2 = ss; //Copy constructor is called +2

    std::cout << "String get test for ss2: " << *ss2.get() << std::endl;

    SmartString ss3(ss); //+3

    std::cout << "String get test for ss3: " << *ss3.get() << std::endl;

    SmartString ss4(new std::string("world!"));

    std::cout << "String get test for ss4: " << *ss4.get() << std::endl;

    ss4 = ss; //Assignment operator is called

    std::cout << "String get test for ss4 after assignement: " << *ss4.get() << std::endl;

    return 0;
}
