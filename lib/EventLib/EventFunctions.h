#ifndef EVENT_LIST_H
#define EVENT_LIST_H

#include "Event.h"

void normalizeDate(unsigned& day, unsigned& month, int& year);

void saveEventsToFile(Event* head, const std::string& filename);

void loadEventsFromFile(Event*& head, const std::string& filename);

Event* createEvent();

void sortEventsByDate(Event*& head);

Event* addFirst(Event* head);

Event* addLast(Event* head);

Event* addSortedByDate(Event* head);

void printEvent(const Event* e);

void editEvent(Event*& event);

Event* searchByDate(Event* head);

Event* searchByName(Event* head);

void searchEventsByYear(const Event* head);

void searchEventsByFigure(const Event* head);

Event* deleteEvent(Event* head);

void printList(const Event* head);

void printFullList(const Event* head);
#endif // EVENT_LIST_H

