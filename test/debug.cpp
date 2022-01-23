#include <UEFIWrapper.hpp>
#include <core/tugui.hpp>

using UEFIWrapper::SystemTable;
using namespace TUGUI;

extern "C" void
efi_main(void *ImageHandle __attribute__((unused)), SystemTable::ESystemTable *systemTable) {
    
    TUGUI::PLATFORM::init(systemTable);

    PaintEngine pe;
    
    // test Rect
    Rectangle rect1(50, 50, 300, 400), rect2(500, 500, 100, 30), rect3(240, 500, 100, 80);
    Rectangle rect4(760, 500, 100, 100), rect5(370, 390, 100, 300), rect6(630, 390, 100, 150);

    pe.setColor(RED); pe(rect1);
    pe.setColor(ORANGE); pe(rect2);
    pe.setColor(YELLOW); pe(rect3);
    pe.setColor(GREEN); pe(rect4);
    pe.setColor(CYAN); pe(rect5);
    pe.setColor(BLUE); pe(rect6);

    while(1);
}
