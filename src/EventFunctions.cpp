#include "EventFunctions.h"
#include <iostream>
#include <chrono>
#include <utility>

#include <fstream>
#include <sstream>

//#include <chrono>

void normalizeDate(unsigned& day, unsigned& month, int& year) {
    while (true) {
        if (std::chrono::year_month_day{
                std::chrono::year{year},
                std::chrono::month{month},
                std::chrono::day{day}
            }.ok()) {
            break;
            }

        std::chrono::year_month ym{std::chrono::year{year}, std::chrono::month{month}};
        unsigned daysInMonth = static_cast<unsigned>(
            std::chrono::year_month_day_last{ym / std::chrono::last}.day()
        );

        int i = static_cast<int>(month);

        if (i > 12) {
            year += i / 12;
            i = i % 12;
            if (i == 0) {
                i = 12;
                --year;
            }
        }
        month = static_cast<unsigned>(i);

        if (day > daysInMonth) {
            month += day / daysInMonth;
            day = day % daysInMonth;
            if (day == 0) {
                day = daysInMonth;
                --month;
            }
        }
    }
}



void initializeEvents(Event*& head) {
    head = new Event({std::chrono::year{2024}, std::chrono::month{5}, std::chrono::day{10}},
                     "Conference", "New York", "Dr. Smith", "Success", "Annual Tech Conference");

    head->nextEvent = new Event({std::chrono::year{2023}, std::chrono::month{11}, std::chrono::day{20}},
                                "Workshop", "San Francisco", "Jane Doe", "Completed", "AI Workshop");

    head->nextEvent->nextEvent = new Event({std::chrono::year{2022}, std::chrono::month{7}, std::chrono::day{15}},
                                           "Hackathon", "Berlin", "John Connor", "Winners Announced", "48-hour coding challenge");

    head->nextEvent->nextEvent->nextEvent = new Event({std::chrono::year{2025}, std::chrono::month{1}, std::chrono::day{5}},
                                                      "Startup Meetup", "London", "Elon Musk", "In Progress", "Networking event for startups");

    head->nextEvent->nextEvent->nextEvent->nextEvent = new Event({std::chrono::year{2023}, std::chrono::month{9}, std::chrono::day{30}},
                                                                 "Product Launch", "Tokyo", "CEO of Sony", "Launched", "New PlayStation release");

    sortEventsByDate(head);
}

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
    std::string name, location, figure, results, description;
    unsigned day, month;
    int year;

    std::cout << "Enter event name: ";
    std::getline(std::cin >> std::ws, name);

    std::cout << "Enter event location: ";
    std::getline(std::cin >> std::ws, location);

    std::cout << "Enter historical figure: ";
    std::getline(std::cin >> std::ws, figure);

    std::cout << "Enter results: ";
    std::getline(std::cin >> std::ws, results);

    std::cout << "Enter description: ";
    std::getline(std::cin >> std::ws, description);

    std::cout << "Enter event date (DD MM YYYY): ";
    std::cin >> day >> month >> year;

    normalizeDate(day, month, year);

    std::chrono::year_month_day date{
        std::chrono::year{year},
        std::chrono::month{month},
        std::chrono::day{day}
    };

    return new Event(date, name, location, figure, results, description);
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


void editEvent(Event*& event) {
    Event* oldEvent = searchByName(event);

    if (!oldEvent) return;

    Event* newEvent = createEvent();
    Event* temp = event;

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
    std::cout << "\033[1;31mEvent not found for this date.\033[0m\n";

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
    std::cout << "Event not found with name: " << searchName << "\n";
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
    std::cout << "Deleted" << "\n";
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

