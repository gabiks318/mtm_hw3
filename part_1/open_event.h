#ifndef OPEN_EVENT_H
#define OPEN_EVENT_H
#include "date_wrap.h"
#include "base_event.h"
#include <string>

namespace mtm
{
    class OpenEvent: public BaseEvent{
        public:
        OpenEvent(DateWrap date, string name):BaseEvent(date,name){}
        OpenEvent(const OpenEvent& event):BaseEvent(event){}
        virtual ~OpenEvent() {}
        BaseEvent* clone() const override {
            return new OpenEvent(*this);
        }
    };
}
#endif
