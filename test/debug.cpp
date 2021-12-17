#include <UEFIWrapper.hpp>

using UEFIWrapper::SystemTable;

extern "C" void
efi_main(void *ImageHandle __attribute__((unused)), SystemTable::ESystemTable *systemTable){
    SystemTable::init(systemTable);
    SystemTable::clearScreen();
    SystemTable::OutputString((wchar_t *)L"Hello UEFI...\n");
    while(1);
}
