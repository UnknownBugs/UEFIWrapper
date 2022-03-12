#ifndef __EVENT_WRAPPER_HPP__
#define __EVENT_WRAPPER_HPP__

#include <wrapper/systemtable_wrapper.hpp>

namespace UEFIWrapper {



class Event {

public:
    static void waitKeyboardEvent() {
        SystemTable::waitForEvent(SystemTable::EventTable::WAIT_KEY);
    }

};  // Event

}; // UEFIWrapper

#endif // __EVENT_WRAPPER_HPP__
