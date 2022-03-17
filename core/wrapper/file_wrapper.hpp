/*
 * @Author: SPeak Shen
 * @Date: 2022-03-15 21:09:08
 * @LastEditTime: 2022-03-17 21:19:20
 * @LastEditors: SPeak Shen
 * @Description: 
 * @FilePath: /UEFIWrapper/core/wrapper/file_wrapper.hpp
 * trying to hard.....
 */
#ifndef __FILE_WRAPPER_HPP__
#define __FILE_WRAPPER_HPP__

#include <wrapper/systemtable_wrapper.hpp>

namespace UEFIWrapper {

namespace IO {

constexpr char EOF = '\0';

#define EFI_FILE_MODE_READ      0x0000000000000001
#define EFI_FILE_MODE_WRITE     0x0000000000000002
#define EFI_FILE_MODE_CREATE    0x8000000000000000
#define EFI_FILE_MODE_RW        (EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE)

EFI_GUID SFSP_GUID = {
    0x0964e5b22, 0x6459, 0x11d2,
    {
        0x8e, 0x39, 0x00, 0xa0,
        0xc9, 0x69, 0x72, 0x3b
    }
};

struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
    unsigned long long Revision;
    unsigned long long (*OpenVolume)(
        struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This,
        struct EFI_FILE_PROTOCOL **Root);
};

struct EFI_FILE_PROTOCOL {
    unsigned long long _buf;
    unsigned long long (*Open)(EFI_FILE_PROTOCOL *This,
                struct EFI_FILE_PROTOCOL **NewHandle,
                unsigned short *FileName,
                unsigned long long OpenMode,
                unsigned long long Attributes);
    unsigned long long (*Close)(struct EFI_FILE_PROTOCOL *This);
    unsigned long long _buf2;
    unsigned long long (*Read)(struct EFI_FILE_PROTOCOL *This,
                unsigned long long *BufferSize,
                void *Buffer);
    unsigned long long (*Write)(struct EFI_FILE_PROTOCOL *This,
                    unsigned long long *BufferSize,
                    void *Buffer);
    unsigned long long _buf3[4];
    unsigned long long (*Flush)(struct EFI_FILE_PROTOCOL *This);
};

class File {

    using EFP = EFI_FILE_PROTOCOL;

public:

    File() {
        init();
    }

    void init() {
        SystemTable::locateProtocol(&SFSP_GUID, NULL, (void **)(&__mSFSP));
    }

    bool open(const char *fileName /*, unsigned char status = 0*/) {
        
        auto cPtr = fileName;
        char tempFileName[1024]; tempFileName[0] = '\0';
        unsigned int len = 0;

        auto fPtr = __mRoot;

        while (cPtr != nullptr && *cPtr != '\0') {
            if (*cPtr == '/') {
                tempFileName[len] = '\0';
                fPtr = __open(fPtr, tempFileName);
                if (nullptr == fPtr) return false; 
                len = 0;
            } else {
                tempFileName[len++] = *cPtr;
            }
            cPtr++;
        }

        if (len) {
            tempFileName[len] = '\0';
            fPtr = __open(fPtr, tempFileName);
            if (nullptr == fPtr) return false; 
        }

        __mFile = fPtr;

        return true;
    }

private:

    static EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *__mSFSP;

    EFI_FILE_PROTOCOL *__mRoot;
    EFI_FILE_PROTOCOL *__mFile;

    void __getRoot() {
        __mSFSP->OpenVolume(__mSFSP, &__mRoot);
    }

    EFP * __open(EFP *parent, const char *fileName) {
        EFP *fPtr = nullptr;
        auto status = parent->Open(parent, &fPtr, nullptr, EFI_FILE_MODE_RW, 0);
        if (status) {
            // TO DO
            return nullptr;
        }
        return fPtr;
    }
};  // File

}; // namespace IO

}; // namespace UEFIWrapper

UEFIWrapper::IO::EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* UEFIWrapper::IO::File::__mSFSP = nullptr;

#endif // __FILE_WRAPPER_HPP__