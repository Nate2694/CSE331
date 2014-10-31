#include "HashFunc.h"

using namespace std;

/**
 * Put information about this hash function here
 */
unsigned int HashA(const std::string& s)
{
    if(s.size() > 2){
        char a = s[0];
        char b = s[1];
        char c = s[2];
        unsigned int ret = 27 * a + 28 * b + c;
        //std::cout << ret<< std::endl;
        return ret;
    }
    else if(s.size() > 1){
        char a = s[0];
        char b = s[1];
        unsigned int ret = 27 * a + b;
        //std::cout << ret<< std::endl;
        return ret;
    }
    else{
        char a = s[0];
        unsigned int ret = a;
        std::cout << ret<< std::endl;
        return ret;
    }
    
}

/**
 * Put information about this hash function here
 */
unsigned int HashB(const std::string& s)
{
    char a = s[0];
    char b;
    (s.size() > 1) ? b = s[1] : b = 20;
    return a * 37 + b;
    
}

/**
 * Put information about this hash function here
 */
unsigned int HashC(const std::string& s)
{
    char a = s[0];
    char b, c;
    
    (s.size() > 1) ? b = s[1] : b = 33;
    
    (s.size() > 2) ? c = s[2] : c = 69;
    
    return a * 10 + b * 11 + c;
}