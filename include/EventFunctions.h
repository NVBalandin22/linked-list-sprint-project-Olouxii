#ifndef EVENT_LIST_H
#define EVENT_LIST_H

#include "Event.h"


void saveEventsToFile(Event* head);

void loadEventsFromFile(Event*& head);

Event* createEvent();

void sortEventsByDate(Event*& head);

Event* addFirst(Event* head);

Event* addLast(Event* head);

Event* addSortedByDate(Event* head);

void printEvent(const Event* e);

void editEvent(Event*& event);

Event* searchByDate(Event* head);

Event* searchByName(Event* head);

Event* deleteEvent(Event* head);

void printList(const Event* head);

void printFullList(const Event* head);
#endif // EVENT_LIST_H
