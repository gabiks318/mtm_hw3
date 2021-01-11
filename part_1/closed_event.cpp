#include "base_event.h"
#include "exceptions.h"
#include "closed_event.h"
#include "./linked_list/linked_list.h"

using mtm::BaseEvent;
using mtm::ClosedEvent;
using mtm::List;

#define MIN_ID 1
#define MAX_ID 1234567890

ClosedEvent::ClosedEvent(DateWrap date, string name):BaseEvent(date, name), allowed_participants(){
}

ClosedEvent::ClosedEvent(const ClosedEvent& event): BaseEvent(event), allowed_participants(event.allowed_participants){
}

ClosedEvent& ClosedEvent::operator=(const ClosedEvent& event){
    if(*this == event){
        return *this;
    }
    name = event.name;
    date = event.date;
    participants = event.participants;
    allowed_participants = event.allowed_participants;
    return *this;
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