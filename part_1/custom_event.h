#ifndef CUSTOM_EVENT_H
#define CUSTOM_EVENT_H
#include "date_wrap.h"
#include "base_event.h"
#include <string>

#define MIN_ID 1
#define MAX_ID 20000

namespace mtm
{
    template <class CanRegister>
    class CustomEvent : public BaseEvent
    {
        CanRegister check_condition;
        public:
        CustomEvent(DateWrap date, string name, CanRegister check_condition);
        CustomEvent(const CustomEvent& event);
        ~CustomEvent() override {}
        void registerParticipant(int student) override;
        BaseEvent* clone() const override;
    };
    //==============Implementation==========//
    template <class CanRegister>
    CustomEvent<CanRegister>::CustomEvent(DateWrap date, string name, CanRegister check_condition) 
                                            :BaseEvent(date,name), check_condition(check_condition){}

    template <class CanRegister>                                                                                        
    CustomEvent<CanRegister>::CustomEvent(const CustomEvent& event): BaseEvent(event){
        check_condition = event.check_condition;
    }

    template <class CanRegister>
    void CustomEvent<CanRegister>::registerParticipant(int student){
    if(student < MIN_ID || student > MAX_ID){
        throw InvalidStudent();
    }
    if (check_condition(student)){
        if (participants.exists(student)){
            throw AlreadyRegistered();
        }
    participants.insert(student);
    } else {
        // TODO: check the exception needed here
        throw RegistrationBlocked();
        }
    }

    template <class CanRegister>
    BaseEvent* CustomEvent<CanRegister>::clone() const {
    return new CustomEvent(*this);
    }
} 
#endif
