#ifndef COMPARE_FUNCTIONS_H
#define COMPARE_FUNCTIONS_H
#include "base_event.h"

namespace mtm{
    class CompareInt{
        public:
        bool operator()(const int,const int);
    };
    /*class ComparePointerEvents{
    public:
    bool operator()(const mtm::BaseEvent*, const mtm::BaseEvent*);
    };*/
}

#endif