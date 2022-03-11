#include <UEFIWrapper.hpp>

using namespace UEFIWrapper;

extern "C" void
efi_main(void *ImageHandle __attribute__((unused)), SystemTable::ESystemTable *systemTable) {

    SystemTable::init(systemTable);
    SystemTable::clearScreen();

    IO::Output cout; cout.init();
    IO::Input cin; cin.init();

    cout << " Test GetChar --> " << IO::endl;

    char c;
    int cnt = 0;
    while (cin >> c && c != 'q') {
        cout << c << " ; cnt = " << cnt++ << IO::endl;
    }
}