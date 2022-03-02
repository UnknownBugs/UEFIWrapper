#include <UEFIWrapper.hpp>

using namespace UEFIWrapper;

extern "C" void
efi_main(void *ImageHandle __attribute__((unused)), SystemTable::ESystemTable *systemTable) {

    while(1);
}
