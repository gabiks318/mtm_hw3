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
        CustomEvent(DateWrap date, string name, CanRegister check_condition):BaseEvent(date,name), check_condition(check_condition){}
        CustomEvent(const CustomEvent& event):BaseEvent(event){
            check_condition = event.check_condition;
        }
        ~CustomEvent() override {}
        void registerParticipant(int student) override{
            if (check_condition(student)){
                if (participants.exists(student)){
                    throw AlreadyRegistered();
                }
                participants.insert(student);
            }
        }
        BaseEvent* clone() const override {
            return new CustomEvent(*this);
        }    
    };
} 
#endif
