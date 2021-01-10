#include <iostream>
#include "base_event.h"
#include "exceptions.h"
#include <string>
#include "./linked_list/linked_list.h"

using mtm::BaseEvent;
using mtm::List;
using std::ostream;

#define MIN_ID 1
#define MAX_ID 1234567890

BaseEvent::BaseEvent(DateWrap date, string name): date(date), name(name), participants(){
}

BaseEvent::BaseEvent(const BaseEvent& event):  date(event.date), name(event.name), participants(event.participants){
}

BaseEvent& BaseEvent::operator=(const BaseEvent& event){
    if(this == &event){
        return *this;
    }
    delete &name;
    delete &date;
    delete &participants;
    name = *(new string(event.name));
    date = *(new DateWrap(event.date));
    participants = *(new List<int>(event.participants));
    return *this;
}

void BaseEvent::registerParticipant(int student){
    if(student < MIN_ID || student > MAX_ID){
        throw InvalidStudent();
    }
    if(participants.exists(student)){
        throw AlreadyRegistered();
    }
    participants.insert(student);
}

void BaseEvent::unregisterParticipant(int student){
    if(student < MIN_ID || student > MAX_ID){
        throw InvalidStudent();
    }
    if(!participants.exists(student)){
        throw NotRegistered();
    }
    participants.remove(student);
} 

bool BaseEvent::operator<(const BaseEvent& event) const{
    return date < event.date;
}

bool BaseEvent::operator==(const BaseEvent& event) const{
    return name == event.getName() && date == event.getDate(); 
}

ostream& BaseEvent::printShort(ostream& os){
    return os << name << " " << date << "\n";
}

ostream& BaseEvent::printLong(ostream& os){
    ostream& os_2 = printShort(os);
    for(int i = 0; i < participants.getSize(); i++){
            os_2<< participants[i] << "\n";
        
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
