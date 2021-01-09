#ifndef BASE_EVENT_H
#define BASE_EVENT_H
#include "date_wrap.h"
#include <string>
#include "./linked_list/linked_list.h"


using std::string;
using mtm::DateWrap;
using std::ostream; 

namespace mtm{

    class BaseEvent{
        protected:
        DateWrap date;
        string name;
        List<int> participants;
        public:
        BaseEvent(DateWrap date, string name);
        BaseEvent(const BaseEvent& event);
        bool operator==(const BaseEvent& event) const;
        virtual ~BaseEvent() {};
        virtual void registerParticipant(int student);
        virtual void unregisterParticipant(int student);
        virtual ostream& printShort(ostream& os);
        virtual ostream& printLong(ostream& os);
        virtual BaseEvent* clone() const = 0;

        DateWrap getDate() const;
        string getName() const;
        List<int> getParticipants() const;
        };
        
}

#endif