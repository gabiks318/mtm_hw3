#ifndef CLOSED_EVENT_H
#define CLOSED_EVENT_H
#include "date_wrap.h"
#include "base_event.h"
#include <string>
#include "./linked_list/linked_list.h"
#include "compare_functions.h"

namespace mtm
{
    class ClosedEvent: public BaseEvent
    {
        List<int,mtm::CompareInt> allowed_participants;
        public:
        ClosedEvent(DateWrap date, string name);
        ClosedEvent(const ClosedEvent&);
        ClosedEvent& operator=(const ClosedEvent&);
        ~ClosedEvent() = default;

        void addInvitee(int student);
        void registerParticipant(int student) override;
        BaseEvent* clone() const override;
        List<int,mtm::CompareInt> getInvitees() const;
    };
}
#endif