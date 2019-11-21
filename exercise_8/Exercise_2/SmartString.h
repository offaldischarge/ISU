#include <string>

class SmartString {
public:
    SmartString(std::string*);
    ~SmartString();
    std::string* get();
    std::string* operator->();
    std::string& operator*();
    SmartString(const SmartString&);
    SmartString& operator=(const SmartString&);
private:
    std::string* str_;
    unsigned int* counter_;
};
