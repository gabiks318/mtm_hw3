#include "base_event.h"
#include "exceptions.h"
#include "closed_event.h"
#include "./linked_list/linked_list.h"

using mtm::BaseEvent;
using mtm::ClosedEvent;

ClosedEvent::ClosedEvent(const ClosedEvent& event): BaseEvent(event){
    List<int> allowed_participants = event.allowed_participants;
}

void ClosedEvent::addInvitee(int student){
    if(allowed_participants.exists(student)){
       throw AlreadyInvited();
    }
    allowed_participants.insert(student);
}

void ClosedEvent::registerParticipant(int student){
    if(participants.exists(student)){
        throw AlreadyRegistered();
    }
    if(allowed_participants.exists(student)){
        participants.insert(student); //TODO : what if student not allowed to register?
    }else{ 
            throw RegistrationBlocked();
        }
}

BaseEvent* ClosedEvent::clone() const{
    return new ClosedEvent(*this);
}