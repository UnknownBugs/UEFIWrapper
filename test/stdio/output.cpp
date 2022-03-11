#include <UEFIWrapper.hpp>

using namespace UEFIWrapper;

extern "C" void
efi_main(void *ImageHandle __attribute__((unused)), SystemTable::ESystemTable *systemTable) {
    
    SystemTable::init(systemTable);
    SystemTable::clearScreen();

    IO::Output cout; cout.init();

    cout << " hello world! --> " << 2022  << IO::endl;

    while(1);
}