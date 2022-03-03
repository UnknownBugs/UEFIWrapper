#ifndef __IO_WRAPPER_HPP__
#define __IO_WRAPPER_HPP__

#include <wrapper/systemtable_wrapper.hpp>


namespace UEFIWrapper {
namespace IO {

union Char {
    char c;
    unsigned short wC;

    Char() = default;
    Char(char _c)  : c { _c } {  }
    Char(unsigned short _wC) : wC { _wC } {  }

} __attribute__ ((packed));


inline static 
void putChar(char c) {
    if (c == '\n') {
        putChar('\r');
    }
    Char temp[2] { Char(c), Char('\0') };
    SystemTable::OutputString(&(temp[0].wC));
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

inline static 
char getChar() {

    EFI_INPUT_KEY key;
    SystemTable::readKeyStroke(&key);

    // type cast
    Char temp(key.UnicodeChar); // temp.wC = key.UnicodeChar;

    return temp.c;
}

};  // namespace IO

}; // namespace UEFIWrapper

#endif // __IO_WRAPPER_HPP__
