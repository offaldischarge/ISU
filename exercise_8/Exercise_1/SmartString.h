#include <string>

class SmartString {
public:
    SmartString(std::string*);
    ~SmartString();
    std::string* get();
    std::string* operator->();
    std::string& operator*();
private:
    SmartString(const SmartString&);
    SmartString& operator=(const SmartString&);

    std::string* str_;
};
