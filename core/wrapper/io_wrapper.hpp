#ifndef __IO_WRAPPER_HPP__
#define __IO_WRAPPER_HPP__

#include <wrapper/systemtable_wrapper.hpp>
#include <wrapper/event_wrapper.hpp>
#include <wrapper/sds.hpp>

namespace UEFIWrapper {
namespace IO {

constexpr char LF = '\n';
constexpr char CR = '\r';

constexpr char endl = LF;


constexpr unsigned int MAX_INPUT_BUFFER_SIZE = 2048 + 1;

union Char {
    char c;
    unsigned short wC;

    Char() = default;
    Char(char _c)  : c { _c } {  }
    Char(unsigned short _wC) : wC { _wC } {  }

} __attribute__ ((packed));


inline static 
void __putChar(char c) {
    if (c == '\n') {
        __putChar('\r');
    }
    Char temp[2] { Char(c), Char('\0') };
    SystemTable::OutputString(&(temp[0].wC));
}

inline static 
char __getChar() {

    EFI_INPUT_KEY key;

    Event::waitKeyboardEvent();
    SystemTable::readKeyStroke(&key);

    // type cast
    Char temp(key.UnicodeChar); // temp.wC = key.UnicodeChar;

    return temp.c;
}



class Output {

    using PutChar = void (*)(char c);

public: // big Five

    void init(const PutChar &pc = __putChar) {
        __mPutChar = pc;
    }

    // copy
    Output(const Output &) = delete;
    Output & operator=(const Output &) = delete;
    // move
    Output(Output &&) = delete;
    Output & operator=(Output &&) = delete;
    
public: // op

    // Note: globle var is not exec ctor
    Output() = default;

    Output & operator<<(char c) {
        __mPutChar(c);
        return *this;
    }

    Output & operator<<(const char *str) {
        auto cPtr = str;
        while (*cPtr != '\0') {
            __putChar(*cPtr);
            cPtr++;
        }
        return *this;
    }

    Output & operator<<(int n) {  *this << static_cast<long long>(n); return *this; }

    Output & operator<<(long n) {  *this << static_cast<long long>(n); return *this; }

    Output & operator<<(long long n) {
        if (n < 0) {
            __mPutChar('-');
            n = -n;
        } else if (n == 0) {
            operator<<('0');
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
            *this << (str + strBegin);
        }

        return *this;
    }

    operator bool() const {
        return true;
    }


private:

    PutChar __mPutChar;

};

class Input {

    using GetChar = char (*)();

public: // big Five

    void init(const GetChar &gc = __getChar) {
        __mGetChar = gc;
        __mInputState = true;
        __mInputBuffer.init();
    }

    // copy
    Input(const Input &) = delete;
    Input & operator=(const Input &) = delete;
    // move
    Input(Input &&) = delete;
    Input & operator=(Input &&) = delete;
    
public: // op

    // Note: globle var is not exec ctor
    Input() = default;

    Input & operator>>(char &c) {
        __getInputBuffer();
        
        if (!__mInputBuffer.empty())
            c = __mInputBuffer.get();

        return *this;
    }

    Input & operator>>(int &n) {  operator>>(n); return *this; }

    Input & operator>>(long &n) {  operator>>(n); return *this; }

    Input & operator>>(long long &n) {
        
        __getInputBuffer();

        char c = '+'; n = 0;
        int flag = 1;
        
        if (!__mInputBuffer.empty()) c = __mInputBuffer.get();
        if ('-' == c) flag = -1;

        while (!__mInputBuffer.empty() && (c = __mInputBuffer.get()) && '9' >= c && '0' <= c) {
            n = n * 10 + (c - '0');
        }
        
        n *= flag;

        return *this;
    }

    operator bool() const {
        return __mInputState;
    }

private:

    GetChar __mGetChar;
    bool __mInputState;
    // Static Queue
    SQueue<char, MAX_INPUT_BUFFER_SIZE> __mInputBuffer;

    void __getInputBuffer() {
        __mInputState = true;
        if (!__mInputBuffer.empty()) return;
        char c;
        while (__mInputBuffer.size() < MAX_INPUT_BUFFER_SIZE && (c = __mGetChar()) && c != CR) {
            __putChar(c);
            __mInputBuffer.put(c);
        }
        if (__mInputBuffer.size() == MAX_INPUT_BUFFER_SIZE) {
            c = __mGetChar();
            __mInputBuffer.put(c);
            // buff overflow
            __mInputState = false;
        }
        __putChar(endl);
    }

};

};  // namespace IO

}; // namespace UEFIWrapper

#endif // __IO_WRAPPER_HPP__
