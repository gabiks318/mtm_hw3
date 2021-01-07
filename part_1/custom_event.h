#ifndef CUSTOM_EVENT_H
#define CUSTOM_EVENT_H
#include "date_wrap.h"
#include "base_event.h"
#include <string>

namespace mtm
{
    template <class CanRegister>
    class CustomEvent : public BaseEvent
    {
    CanRegister check_condition;
    public:
        CustomEvent(DateWrap date, string name, CanRegister check_condition):BaseEvent(date,name), check_condition(check_condition{}
        void registerParticipant(int student) const override{
            if (check_condition(student))
            {
                if (participants[student])
                {
                    throw AlreadyRegistered();
                }
                participants[student] = true;
            }
        }
    }
} // namespace mtm
#endif
