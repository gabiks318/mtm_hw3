#ifndef BASE_EVENT_H
#define BASE_EVENT_H
#include "date_wrap.h"
#include <string>

using std::string;
using mtm::DateWrap;
using std::ostream; 
#define MAX_PARTICIPANTS 20000

namespace mtm{

    class BaseEvent{
        DateWrap date;
        string name;
        bool* participants;
        public:
        BaseEvent(DateWrap date, string name);/* : date(date), name(name), participants()
        {
            participants = new bool[MAX_PARTICIPANTS];
        } */
        BaseEvent(const BaseEvent& event);
        ~BaseEvent() {
            delete[] participants;
        }
        virtual void registerParticipant(int student) const;
        virtual void unregistrParticpant(int student) const;
        virtual ostream& printShort(ostream& os);
        virtual ostream& printLong(ostream& os);
        virtual BaseEvent* clone() = 0;
        };
        
}

#endif