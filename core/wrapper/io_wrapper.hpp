#ifndef __IO_WRAPPER_HPP__
#define __IO_WRAPPER_HPP__

#include <wrapper/systemtable_wrapper.hpp>


namespace UEFIWrapper {
namespace IO {

inline static 
void putChar(char c) {
    if (c == '\n') {
        putChar('\r');
    }
    unsigned short wc = c;
    unsigned short temp[2] = {wc, '\0'};
    SystemTable::OutputString(temp);
}

inline static
void putStr(const char *s) {
    auto cPtr = s;
    while (*cPtr != '\0') {
        putChar(*cPtr);
        cPtr++;
    }
}

inline static
void putInteger(long long n) {
    if (n < 0) {
        putChar('-');
        n = -n;
    }

    char str[101] { };

    int strBegin = 100;

    str[strBegin] = '\0';

    while (n && strBegin >= 0) {
        strBegin--;
        str[strBegin] = n % 10 + '0';
        n /= 10; 
    }

    if (strBegin >= 0) {
        putStr(str + strBegin);
    }
}

};  // namespace IO

}; // namespace UEFIWrapper

#endif // __IO_WRAPPER_HPP__
