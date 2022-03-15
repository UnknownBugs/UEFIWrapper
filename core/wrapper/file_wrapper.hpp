/*
 * @Author: SPeak Shen
 * @Date: 2022-03-15 21:09:08
 * @LastEditTime: 2022-03-15 21:36:35
 * @LastEditors: SPeak Shen
 * @Description: 
 * @FilePath: /UEFIWrapper/core/wrapper/file_wrapper.hpp
 * trying to hard.....
 */
#ifndef __File_WRAPPER_HPP__
#define __File_WRAPPER_HPP__

#include <wrapper/systemtable_wrapper.hpp>

namespace UEFIWrapper {

const struct EFI_GUID SFSP_GUID = {
    0x0964e5b22, 0x6459, 0x11d2,
    {
        0x8e, 0x39, 0x00, 0xa0,
        0xc9, 0x69, 0x72, 0x3b
    }
};

class File {

    struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
        unsigned long long Revision;
        unsigned long long (*OpenVolume)(
            struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This,
            struct EFI_FILE_PROTOCOL **Root);
    };

    struct EFI_FILE_PROTOCOL {
        unsigned long long _buf;
        unsigned long long (*Open)(struct EFI_FILE_PROTOCOL *This,
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

public:

    void init() {
        SystemTable::locateProtocol(&SFSP_GUID, NULL, static_cast<void **>(&__mSFSP))
    }

private:
    static EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *__mSFSP;

    EFI_FILE_PROTOCOL *__mRoot

    void __getRoot() {
        status = SFSP->OpenVolume(SFSP, &__mRoot);
    }
};  // File

}; // UEFIWrapper

#endif // __File_WRAPPER_HPP__