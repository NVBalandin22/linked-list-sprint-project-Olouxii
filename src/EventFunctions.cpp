#include "EventFunctions.h"
#include <iostream>
#include <chrono>
#include <utility>

Event* createEvent(Event* head) {
    std::string newName, newLocation, newFigure, newResult, newDescription;
    int year;
    unsigned day, month;

    std::cout << "Enter event name: ";
    std::getline(std::cin, newName);

    std::cout << "Enter event location: ";
    std::getline(std::cin, newLocation);

    std::cout << "Enter key figure of the event: ";
    std::getline(std::cin, newFigure);

    std::cout << "Enter event result: ";
    std::getline(std::cin, newResult);

    std::cout << "Enter event description: ";
    std::getline(std::cin, newDescription);

    std::cout << "Enter day, month, year: ";
    std::cin >> day >> month >> year;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto newDate = std::chrono::year_month_day{std::chrono::year{year}, std::chrono::month{month}, std::chrono::day{day}};
    auto newEvent = new Event{newDate, newName, newLocation, newFigure, newResult, newDescription};

    return newEvent;
}

Event* addFirst(Event* head) {
    Event *newEvent = createEvent(head);
    newEvent->nextEvent = head;
    return newEvent;
}

Event* addLast(Event* head) {
    Event *newEvent = createEvent(head);
    if (!head) return newEvent;
    Event* curr = head;
    while (curr->nextEvent) {
        curr = curr->nextEvent;
    }
    curr->nextEvent = newEvent;
    return head;
}

Event* addSortedByDate(Event* head) {
    Event *newEvent = createEvent(head);
    if (!head || newEvent->date < head->date) {
        return addFirst(head, newEvent);
    }
    Event* curr = head;
    while (curr->nextEvent && curr->nextEvent->date < newEvent->date) {
        curr = curr->nextEvent;
    }
    newEvent->nextEvent = curr->nextEvent;
    curr->nextEvent = newEvent;
    return head;
}


void editEvent(Event* event, std::string newName, std::string newLocation,
               std::string newFigure, std::string newResults, std::string newDescription) {
    if (event) {
        event->name = std::move(newName);
        event->location = std::move(newLocation);
        event->figure = std::move(newFigure);
        event->results = std::move(newResults);
        event->description = std::move(newDescription);
    }
}

Event* searchByDate(Event* head, std::chrono::year_month_day searchDate) {
    Event* curr = head;
    while (curr) {
        if (curr->date == searchDate) {
            return curr;
        }
        curr = curr->nextEvent;
    }
    return nullptr;
}


Event* searchByName(Event* head, const std::string& searchName) {
    Event* curr = head;
    while (curr) {
        if (curr->name == searchName) {
            return curr;
        }
        curr = curr->nextEvent;
    }
    return nullptr;
}

Event* deleteEvent(Event* head, const Event* eventToDelete) {
    if (!head) return nullptr;

    if (head == eventToDelete) {
        const Event* temp = head;
        head = head->nextEvent;
        delete temp;
        return head;
    }
//dwr3
 //d
    Event* curr = head;
    while (curr->nextEvent && curr->nextEvent != eventToDelete) {
        curr = curr->nextEvent;
    }

    if (curr->nextEvent == eventToDelete) {
        const Event* temp = curr->nextEvent;
        curr->nextEvent = curr->nextEvent->nextEvent;
        delete temp;
    }

    return head;
}


void printList(const Event* head) {
    const Event* current = head;
    while (current) {
        std::cout << current->name << " ("
                  << static_cast<unsigned>(current->date.day()) << "."
                  << static_cast<unsigned>(current->date.month()) << "."
                  << static_cast<int>(current->date.year()) << ")\n";
        current = current->nextEvent;
    }
}

