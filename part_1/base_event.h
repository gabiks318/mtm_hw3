#ifndef BASE_EVENT_H
#define BASE_EVENT_H
#include "date_wrap.h"
#include <string>
#include "./linked_list/linked_list.h"
#include "compare_functions.h"

using std::string;
using mtm::DateWrap;
using std::ostream; 

namespace mtm{

    class BaseEvent{
        protected:
        DateWrap date;
        string name;
        List<int,mtm::CompareInt> participants;
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
        DateWrap getDate() const;
        string getName() const;
        List<int,mtm::CompareInt> getParticipants() const;

        /*class CompareInt{
        public:
        bool operator()(int,int);
        };*/
    };      
}
   

#endif