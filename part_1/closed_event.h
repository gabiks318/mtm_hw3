#ifndef CLOSED_EVENT_H
#define CLOSED_EVENT_H
#include "date_wrap.h"
#include "base_event.h"
#include <string>

namespace mtm
{
    class ClosedEvent: public BaseEvent{
        bool* allowed_participants;
        public:
        ClosedEvent(DateWrap date, string name):BaseEvent(date, name), allowed_participants(){
            allowed_participants = new bool[MAX_PARTICIPANTS];
        }
        void addInvitee(int student){
            if(allowed_participants[student]){
                throw AlreadyInvited();
            }
            allowed_participants[student] = true;
        }
        void registerParticipant(int student) const override{
            if(participants[student]){
                throw AlreadyRegistered();
            }
            if(allowed_participants[student]){
                participants[student] = true; //TODO : what if student not allowed to register?
            }
        }
    }
}
#endif