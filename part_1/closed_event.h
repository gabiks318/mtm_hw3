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
        List<int,CompareInt> allowed_participants;
        public:
        ClosedEvent(DateWrap date, string name);
        ClosedEvent(const ClosedEvent&);
        ClosedEvent& operator=(const ClosedEvent&);
        ~ClosedEvent() = default;

        void addInvitee(int student);
        void registerParticipant(int student) override;
        BaseEvent* clone() const override;
        List<int,CompareInt> getInvitees() const;
        bool isInvited(int student);
    };
}
#endif