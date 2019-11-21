#include "SmartString.h"

SmartString::SmartString(std::string* str) : str_(str){}

SmartString::~SmartString(){
    delete str_;
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

SmartString::SmartString(const SmartString& other){
    //empty
}

SmartString& SmartString::operator=(const SmartString&){
    //empty
}
