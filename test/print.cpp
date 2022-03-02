#include <UEFIWrapper.hpp>

using namespace UEFIWrapper;

extern "C" void
efi_main(void *ImageHandle __attribute__((unused)), SystemTable::ESystemTable *systemTable) {
    
    SystemTable::init(systemTable);
    SystemTable::clearScreen();

    IO::putChar('E');
    IO::putChar('\n');

    IO::putStr("Hellow World!\n");

    IO::putInteger(-1234567890);

    while(1);
}
