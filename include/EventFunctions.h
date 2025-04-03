#ifndef EVENT_LIST_H
#define EVENT_LIST_H

#include "Event.h"

Event* createEvent(Event* head);

Event* addFirst(Event* head);

Event* addLast(Event* head);

Event* addSortedByDate(Event* head);

void editEvent(Event* event, std::string newName, std::string newLocation,
               std::string newFigure, std::string newResults, std::string newDescription);

Event* searchByDate(Event* head, std::chrono::year_month_day searchDate);

Event* searchByName(Event* head, const std::string& searchName);

Event* deleteEvent(Event* head, const Event* eventToDelete);

void printList(const Event* head);

#endif // EVENT_LIST_H
