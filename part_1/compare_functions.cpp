#include "compare_functions.h"

bool mtm::CompareInt::operator()(const int first,const int second){
    return first < second;
}

/*bool mtm::ComparePointerEvents::operator()(const mtm::BaseEvent* event1, const mtm::BaseEvent* event2)
 {
    if(event1->getDate() < event2->getDate()){
        return true;
    }
    if(event1->getDate() == event2->getDate()){
        if(event1->getName() < event2->getName())
            return true;
    }
    return false;
 }*/
