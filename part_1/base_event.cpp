#include <iostream>
#include "base_event.h"
#include "exceptions.h"
#include <string>
#include "./linked_list/linked_list.h"

using mtm::BaseEvent;
using mtm::List;
using std::ostream;
using std::endl;

BaseEvent::BaseEvent(DateWrap date, string name): date(date), name(name), participants(){
}

BaseEvent::BaseEvent(const BaseEvent& event):  date(event.date), name(event.name), participants(event.participants){
}

BaseEvent& BaseEvent::operator=(const BaseEvent& event){
    if(*this == event){
        return *this;
    }
    name = event.name;
    date = event.date;
    participants = event.participants;
    return *this;
}

void BaseEvent::registerParticipant(int student){
    if(student < min_id || student > max_id){
        throw InvalidStudent();
    }
    if(participants.exists(student)){
        throw AlreadyRegistered();
    }
    participants.insert(student);
}

bool BaseEvent::operator>=(const BaseEvent& event) const{
    return !(*this < event);
}

void BaseEvent::unregisterParticipant(int student){
    if(student < min_id || student > max_id){
        throw InvalidStudent();
    }
    if(!participants.exists(student)){
        throw NotRegistered();
    }
    participants.remove(student);
} 

/*bool mtm::operator<(const BaseEvent* event1,const BaseEvent* event2){
     if(event1->getDate() < event2->getDate()){
        return true;
    }
    if(event1->getDate() == event2->getDate()){
        if(event1->getName() < event2->getName())
            return true;
    }
   // *event1 < *event2
    return false;
}*/

bool BaseEvent::operator<(const BaseEvent& event) const{
    if(date < event.getDate()){
        return true;
    }
    if(date == event.getDate()){
        if(name < event.getName())
            return true;
    }
    return false;
}

bool BaseEvent::operator==(const BaseEvent& event) const{
    return name == event.getName() && date == event.getDate(); 
}

ostream& BaseEvent::printShort(ostream& os){
    return os << name << " " << date << endl;
}

ostream& BaseEvent::printLong(ostream& os){
    ostream& os_2 = printShort(os);
    for(int i = 0; i < participants.getSize(); i++){
        os_2<< participants[i] << endl; 
    }
    return os_2;
}

DateWrap BaseEvent::getDate() const{
    return date;
}

string BaseEvent::getName() const {
    return name;
}

List<int> BaseEvent::getParticipants() const{
    return participants;
}
