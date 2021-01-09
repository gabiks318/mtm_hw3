#include "base_event.h"
#include "exceptions.h"
#include "closed_event.h"
#include "./linked_list/linked_list.h"

using mtm::BaseEvent;
using mtm::ClosedEvent;
using mtm::List;

#define MIN_ID 1
#define MAX_ID 20000

ClosedEvent::ClosedEvent(const ClosedEvent& event): BaseEvent(event), allowed_participants(event.allowed_participants){
}

void ClosedEvent::addInvitee(int student){
    if(student < MIN_ID || student > MAX_ID){
        throw InvalidStudent();
    }
    if(allowed_participants.exists(student)){
       throw AlreadyInvited();
    }
    allowed_participants.insert(student);
}

void ClosedEvent::registerParticipant(int student){
    if(student < MIN_ID || student > MAX_ID){
        throw InvalidStudent();
    }
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

List<int> ClosedEvent::getInvitees() const{
    return allowed_participants;
}