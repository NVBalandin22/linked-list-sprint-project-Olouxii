#include "EventFunctions.h"
#include <iostream>
#include <chrono>
#include <utility>

#include <fstream>
#include <sstream>


void saveEventsToFile(Event* head) {
    std::ofstream file("events.txt");
    if (!file) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    Event* current = head;
    while (current) {
        file << static_cast<int>(current->date.year()) << " "
             << static_cast<unsigned>(current->date.month()) << " "
             << static_cast<unsigned>(current->date.day()) << "\n"
             << current->name << "\n"
             << current->location << "\n"
             << current->figure << "\n"
             << current->results << "\n"
             << current->description << "\n"
             << "---\n";
        current = current->nextEvent;
    }

    file.close();
}

void loadEventsFromFile(Event*& head) {
    std::ifstream file("events.txt");
    if (!file) {
        std::cerr << "No saved data found, starting with an empty list." << std::endl;
        return;
    }

    std::string name, location, figure, results, description, line;
    int year;
    unsigned month, day;

    Event* tempHead = nullptr;
    Event** current = &tempHead;

    while (true) {
        file >> year >> month >> day;
        file.ignore();

        if (file.eof()) break;

        std::getline(file, name);
        std::getline(file, location);
        std::getline(file, figure);
        std::getline(file, results);
        std::getline(file, description);
        std::getline(file, line);

        *current = new Event({std::chrono::year{year}, std::chrono::month{month}, std::chrono::day{day}},
                             name, location, figure, results, description);
        current = &((*current)->nextEvent);
    }

    head = tempHead;
    file.close();
}


Event::Event(std::chrono::year_month_day d, std::string n, std::string loc,
             std::string fig, std::string res, std::string desc)
    : date(d), name(std::move(n)), location(std::move(loc)), figure(std::move(fig)), results(std::move(res)), description(std::move(desc)), nextEvent(nullptr) {}

Event* createEvent() {
    std::string newName, newLocation, newFigure, newResult, newDescription;
    int year;
    unsigned day, month;

    std::cout << "Enter event name: ";
    std::getline(std::cin, newName);

    std::cout << "Enter event location(s): ";
    std::getline(std::cin, newLocation);

    std::cout << "Enter key figure(s) of the event: ";
    std::getline(std::cin, newFigure);

    std::cout << "Enter event result: ";
    std::getline(std::cin, newResult);

    std::cout << "Enter event description: ";
    std::getline(std::cin, newDescription);

    std::cout << std::endl << "Enter day, month, year: ";
    std::cin >> day >> month >> year;

    auto newDate = std::chrono::year_month_day{std::chrono::year{year}, std::chrono::month{month}, std::chrono::day{day}};
    auto newEvent = new Event{newDate, newName, newLocation, newFigure, newResult, newDescription};

    return newEvent;
}



void sortEventsByDate(Event*& head) {
    if (!head || !head->nextEvent) return;

    bool swapped;
    do {
        swapped = false;
        Event** current = &head;

        while ((*current)->nextEvent) {
            if ((*current)->date > (*current)->nextEvent->date) {

                Event* temp = (*current)->nextEvent;
                (*current)->nextEvent = temp->nextEvent;
                temp->nextEvent = *current;
                *current = temp;
                swapped = true;
            }
            current = &((*current)->nextEvent);
        }
    } while (swapped);
}

Event* addFirst(Event* head) {
    Event *newEvent = createEvent();
    newEvent->nextEvent = head;
    return newEvent;
}

Event* addLast(Event* head) {
    Event *newEvent = createEvent();
    if (!head) return newEvent;
    Event* curr = head;
    while (curr->nextEvent) {
        curr = curr->nextEvent;
    }
    curr->nextEvent = newEvent;
    return head;
}

Event* addSortedByDate(Event* head) {
    head = addFirst(head);
    sortEventsByDate(head);

    return head;
}


void editEvent(Event*& head) {
    Event* oldEvent = searchByName(head);
    Event* newEvent = createEvent();
    Event* temp = head;

    while (temp) {
        if (temp == oldEvent) {
            // Swap the values of the events
            temp->date = newEvent->date;
            temp->name = newEvent->name;
            temp->location = newEvent->location;
            temp->figure = newEvent->figure;
            temp->results = newEvent->results;
            temp->description = newEvent->description;
            return;
        }
        temp = temp->nextEvent;
    }
    printEvent(temp);
}

Event* searchByDate(Event* head) {

    int year;
    unsigned day, month;
    std::cout << "Enter day, month, year: ";
    std::cin >> day >> month >> year;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    auto searchDate = std::chrono::year_month_day{std::chrono::year{year}, std::chrono::month{month}, std::chrono::day{day}};

    Event* curr = head;
    while (curr) {
        if (curr->date == searchDate) {
            return curr;
        }
        curr = curr->nextEvent;
    }
    return nullptr;
}


Event* searchByName(Event* head) {
    std::string searchName;
    std::cout << "Enter Event name: ";
    std::getline(std::cin, searchName);

    Event* curr = head;
    while (curr) {
        if (curr->name == searchName) {
            return curr;
        }
        curr = curr->nextEvent;
    }
    return nullptr;
}

Event* deleteEvent(Event* head) {
    Event* eventToDelete = searchByName(head);
    if (!head || !eventToDelete) return head;

    if (head == eventToDelete) {
        Event* temp = head;
        head = head->nextEvent;
        delete temp;
        return head;
    }

    Event* curr = head;
    while (curr->nextEvent && curr->nextEvent != eventToDelete) {
        curr = curr->nextEvent;
    }

    if (curr->nextEvent) {
        Event* temp = curr->nextEvent;
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

void printEvent(const Event* e) {
    if (!e) return;

    std::cout << "----------------------------------\n";
    std::cout << "Name: " << e->name << "\n";
    std::cout << "Date: "
              << static_cast<unsigned>(e->date.day()) << "."
              << static_cast<unsigned>(e->date.month()) << "."
              << static_cast<int>(e->date.year()) << "\n";
    std::cout << "Location: " << e->location << "\n";
    std::cout << "Key Figure: " << e->figure << "\n";
    std::cout << "Result: " << e->results << "\n";
    std::cout << "Description: " << e->description << "\n";
}


void printFullList(const Event* head) {
    const Event* current = head;
    while (current) {
        printEvent(current);
        current = current->nextEvent;
    }
    std::cout << "----------------------------------\n";
}

