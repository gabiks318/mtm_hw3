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
        const int min_id = 1;
        const int max_id = 1234567890;

        public:
        BaseEvent(DateWrap date, string name);
        BaseEvent(const BaseEvent&);
        BaseEvent& operator=(const BaseEvent&); 
        virtual ~BaseEvent() = default;

        bool operator==(const BaseEvent& event) const;
        bool operator<(const BaseEvent& event) const;
        bool operator>=(const BaseEvent&) const;
        virtual void registerParticipant(int student);
        virtual void unregisterParticipant(int student);
        virtual ostream& printShort(ostream& os);
        virtual ostream& printLong(ostream& os);
        virtual BaseEvent* clone() const = 0;
        //friend bool operator<(const BaseEvent*,const BaseEvent*);
        DateWrap getDate() const;
        string getName() const;
        List<int> getParticipants() const;
    };
    //bool operator<(const BaseEvent* event1,const BaseEvent* event2);
}

#endif