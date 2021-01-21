#include "base_event.h"
#include "closed_event.h"
#include "custom_event.h"
#include "open_event.h"
#include "event_container.h"
#include "../partA/exceptions.h"
#include "festival.h"
#include "../partA/date_wrap.h"
#include "../utilities.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>

using mtm::EventContainer;
using mtm::Festival;
using mtm::BaseEvent;
using mtm::OpenEvent;
using mtm::ClosedEvent;
using mtm::CustomEvent;
using mtm::DateWrap;
using std::ostringstream;
using mtm::Divisible2;
using mtm::compare_file_to_buffer;

int main() {
    DateWrap date1(21,4,1999);
    DateWrap date2(21,8,2011);
    //constructor and = tests
    Festival* fest1 = new Festival(date1);
    Festival* fest2 = new Festival(*fest1);
    Festival fest3(date2);
    Festival fest4(date1);
    fest4 = fest3;

    //adding all types of events
    OpenEvent oe1(date1,"a My open birthday!");
    OpenEvent oe2(date2, "a Young Eitan's open birthday");
    ClosedEvent ce1(date1, "c My Closed Birthday..");
    ClosedEvent ce2(date2, "c Young Eitan's Closed Birthday..");
    CustomEvent<Divisible2> cse1(date1, "b My Indie Alternative birthday", Divisible2());
    CustomEvent<Divisible2> cse2(date2, "b Eitan's all week combi marathon", Divisible2());
    fest1->add(oe1);
    fest2->add(oe1);
    try {
        fest3.add(oe1);
        assert(0);
    } catch (mtm::DateMismatch&) {}
    try {
        fest4.add(oe1);
        assert(0);
    } catch (mtm::DateMismatch&) {}
    assert(fest1->size() == 1 && fest2->size() == 1);
    assert(fest3.size() == 0 && fest4.size() == 0);
    fest1->add(ce1);
    fest2->add(ce1);
    try {
        fest3.add(ce1);
        assert(0);
    } catch (mtm::DateMismatch&) {}
    try {
        fest4.add(ce1);
        assert(0);
    } catch (mtm::DateMismatch&) {}
    assert(fest1->size() == 2 && fest2->size() == 2);
    assert(fest3.size() == 0 && fest4.size() == 0);
    fest1->add(cse1);
    fest2->add(cse1);
    try {
        fest3.add(cse1);
        assert(0);
    } catch (mtm::DateMismatch&) {}
    try {
        fest4.add(cse1);
        assert(0);
    } catch (mtm::DateMismatch&) {}
    assert(fest1->size() == 3 && fest2->size() == 3);
    assert(fest3.size() == 0 && fest4.size() == 0);
    fest3.add(cse2);
    fest4.add(cse2);
    try {
        fest1->add(cse2);
        assert(0);
    } catch (mtm::DateMismatch&) {}
    try {
        fest2->add(cse2);
        assert(0);
    } catch (mtm::DateMismatch&) {}
    assert(fest1->size() == 3 && fest2->size() == 3);
    assert(fest3.size() == 1 && fest4.size() == 1);
    fest3.add(ce2);
    fest4.add(ce2);
    try {
        fest1->add(ce2);
        assert(0);
    } catch (mtm::DateMismatch&) {}
    try {
        fest2->add(ce2);
        assert(0);
    } catch (mtm::DateMismatch&) {}
    assert(fest1->size() == 3 && fest2->size() == 3);
    assert(fest3.size() == 2 && fest4.size() == 2);
    fest3.add(oe2);
    fest4.add(oe2);
    try {
        fest1->add(oe2);
        assert(0);
    } catch (mtm::DateMismatch&) {}
    try {
        fest2->add(oe2);
        assert(0);
    } catch (mtm::DateMismatch&) {}
    assert(fest1->size() == 3 && fest2->size() == 3);
    assert(fest3.size() == 3 && fest4.size() == 3);

    //iterator tests
    ostringstream buff;
    for(EventContainer::EventIterator it = (*fest1).begin(); it != (*fest1).end(); ++it){
        (*it).printShort(buff);
    }
    for(EventContainer::EventIterator it = (*fest2).begin(); it != (*fest2).end(); ++it){
        (*it).printShort(buff);
    }
    for(EventContainer::EventIterator it = (fest3).begin(); it != (fest3).end(); ++it){
        (*it).printShort(buff);
    }
    for(EventContainer::EventIterator it = (fest4).begin(); it != (fest4).end(); ++it){
        (*it).printShort(buff);
    }
    compare_file_to_buffer(buff, "./outputs/festival_tests_compare.txt");

    delete fest1;
    delete fest2;
}