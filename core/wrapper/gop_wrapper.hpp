/*
 * @Author: SPeak Shen 
 * @Date: 2021-11-13 23:13:58 
 * @Last Modified by: SPeak Shen
 * @Last Modified time: 2021-11-20 23:36:21
 * 
 * Graphics Output Protocal Wrapper
 * 
 */

#ifndef __GOP_WRAPPER_HPP__
#define __GOP_WRAPPER_HPP__

#include <wrapper/systemtable_wrapper.hpp>

#define EFI_GRAPHICS_OUTPUT_PROTOCAL_GUID { \
    0x9042a9de, 0x23dc, 0x4a38, { \
        0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a \
    }   \
};
namespace UEFIWrapper {
class GOP {
private:
    enum EFI_GRAPHICS_PIXEL_FORMAT {
        PixelRedGreenBlueReserved8BitPerColor,
        PixelBlueGreenRedReserved8BitPerColor,
        PixelBitMask,
        PixelBltOnly,
        PixelFormatMax
    };

    struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL {
        unsigned char blue;
        unsigned char green;
        unsigned char red;
        unsigned char reserved;
    };

    struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION {
        unsigned int version;
        unsigned int horizontalResolution;
        unsigned int verticalResolution;
        EFI_GRAPHICS_PIXEL_FORMAT pixelFormat;
    };

    struct EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE {
        unsigned int maxMode;
        unsigned int mode;
        EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *info;
        unsigned long long sizeOfInfo;
        unsigned long long frameBufferBase;
    };

    struct EFI_GRAPHICS_OUTPUT_PROTOCOL {
        unsigned long long (*queryMode)(
            struct EFI_GRAPHICS_OUTPUT_PROTOCOL *_this,
            unsigned int modeID,
            unsigned long long *sizeOfInfo,
            struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* *info  // equal InfoTypePointer &itp; get back to info  
        );

        unsigned long long (*setMode)(
            struct EFI_GRAPHICS_OUTPUT_PROTOCOL *_this,
            unsigned int modeID
        );

        EFI_GRAPHICS_OUTPUT_BLT_PIXEL blt;
        EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *mode;
    };


public:

    using EGOP          = EFI_GRAPHICS_OUTPUT_PROTOCOL;
    using PixelFormat   = EFI_GRAPHICS_PIXEL_FORMAT;
    using Pixel         = EFI_GRAPHICS_OUTPUT_BLT_PIXEL;

/*----------------------------------------------------------------*/

public:

    GOP();

    void init();

    unsigned long long getFrameBufferBase() const;

    PixelFormat getPixelFormat() const;

    unsigned int getHorizontalResolution() const;

    unsigned int getVerticalResolution() const;

private:
    EGOP *_mEGOP;  // not need to free

};  /* GOP end */

GOP::GOP() {
    SystemTable::EGUID eguid = EFI_GRAPHICS_OUTPUT_PROTOCAL_GUID;
    SystemTable::locateProtocol(&eguid, nullptr, (void **)&_mEGOP);
}

unsigned long long GOP::getFrameBufferBase() const {
    return _mEGOP->mode->frameBufferBase;
}

GOP::PixelFormat GOP::getPixelFormat() const {
    return _mEGOP->mode->info->pixelFormat;
}

unsigned int GOP::getHorizontalResolution() const {
    return _mEGOP->mode->info->horizontalResolution;
}

unsigned int GOP::getVerticalResolution() const {
    return _mEGOP->mode->info->verticalResolution;
}

} //UEFIWrapper

#endif // __GOP_WRAPPER_HPP__