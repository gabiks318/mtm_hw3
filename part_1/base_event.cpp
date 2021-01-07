#include <iostream>
#include "base_event.h"
#include "exceptions.h"

using mtm::BaseEvent;
using std::ostream;

BaseEvent::BaseEvent(DateWrap date, string name): date(date), name(name), participants()
{
            participants = new bool[MAX_PARTICIPANTS];
}

BaseEvent::BaseEvent(const BaseEvent& event){
    name = event.name;
    date = event.date;
    participants = new bool[MAX_PARTICIPANTS];
    for(int i = 0; i < MAX_PARTICIPANTS; i++){
        participants[i] = event.participants[i];
    }
}

void BaseEvent::registerParticipant(int student) const{
    if(participants[student]){
        throw AlreadyRegistered();
    }
    participants[student] = true;
}

void BaseEvent::unregistrParticpant(int student) const{
    if(!participants[student]){
        throw NotRegistered();
    }
    participants[student] = false;
} 

ostream& BaseEvent::printShort(ostream& os){
    return os << name << " " << date << "\n";
}
ostream& BaseEvent::printLong(ostream& os){
    ostream& os_2 = printShort(os);
    for(int i = 1; i < MAX_PARTICIPANTS; i++){
        if(participants[i]){
            os_2<< i << "\n";
        }
    }
    return os_2;
}

BaseEvent* BaseEvent::clone(){
    return new BaseEvent(*this);
}