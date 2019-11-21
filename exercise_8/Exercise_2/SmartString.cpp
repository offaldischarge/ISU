#include "SmartString.h"
#include <iostream>

SmartString::SmartString(std::string* str) : str_(str){
    counter_ = new unsigned int(1);
}

SmartString::~SmartString(){
    --(*counter_);
    if((*counter_) <= 0){
        delete str_;
        delete counter_;
    }
}

std::string* SmartString::get(){
    return str_;
}

std::string* SmartString::operator->(){
    return str_;
}

std::string& SmartString::operator*(){
    return *str_;
}

SmartString::SmartString(const SmartString& other) {
    str_ = other.str_;
    counter_ = other.counter_;
    (*counter_)++;

    std::cout << (*counter_) << std::endl;

    std::cout << "Copy constructor is used!" << std::endl; //for tests
}

SmartString& SmartString::operator=(const SmartString& other){

    std::cout << "Assignment is used!" << std::endl; //for tests

    if(&other != this){
        str_ = other.str_;
        counter_ = other.counter_;
    }
    return *this;

}
