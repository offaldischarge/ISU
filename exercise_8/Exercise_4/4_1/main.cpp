#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>

int main(){

	boost::shared_ptr<std::string> ss(new std::string("Hello"));

    std::cout << "String length: " << ss->length() << std::endl;

    if(ss->find("world") != std::string::npos){
        std::cout << "The 'ss' string does contain 'world'" << std::endl;
    } else {
        std::cout << "The 'ss' string does NOT containt 'world'" << std::endl;
    }

    std::cout << "String get test for ss: " << *ss << std::endl;

    boost::shared_ptr<std::string> ss2 = ss; //Copy constructor is called +2a

    std::cout << "String get test for ss2: " << *ss2 << std::endl;

    boost::shared_ptr<std::string> ss3(ss); //+3

    std::cout << "String get test for ss3: " << *ss3 << std::endl;

    boost::shared_ptr<std::string> ss4(new std::string("world!"));

    std::cout << "String get test for ss4: " << *ss4 << std::endl;

    ss4 = ss; //Assignment operator is called

    std::cout << "String get test for ss4 after assignement: " << *ss4 << std::endl;

    return 0;
}
