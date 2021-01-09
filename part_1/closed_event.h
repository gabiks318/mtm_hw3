#ifndef CLOSED_EVENT_H
#define CLOSED_EVENT_H
#include "date_wrap.h"
#include "base_event.h"
#include <string>
#include "./linked_list/linked_list.h"

namespace mtm
{
    class ClosedEvent: public BaseEvent
    {
        List<int> allowed_participants;
        public:
        ClosedEvent(DateWrap date, string name):BaseEvent(date, name), allowed_participants(){}
        ClosedEvent(const ClosedEvent& event);
        ~ClosedEvent() override {}
        void addInvitee(int student);
        void registerParticipant(int student) override;
        BaseEvent* clone() const override;
        List<int> getInvitees() const;
    };
}
#endif