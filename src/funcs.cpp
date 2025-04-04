#include <chrono>
#include<iostream>
#include "funcs.h"
#include "EventFunctions.h"

using namespace std;

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

int showMainMenu() {
    cout << "\n======== OlouXii Menu ========\n";
    cout << "0 Exit" << endl;
    cout << "1 Add first event" << endl;
    cout << "2 Append event" << endl;
    cout << "3 Add new event and resort list" << endl;
    cout << "4 Edit event" << endl;
    cout << "5 Search event by name" << endl;
    cout << "6 Search event by date" << endl;
    cout << "7 Delete element" << endl;
    cout << "Choose an option: ";

    int user_answer;
    cin >> user_answer;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очищаем после cin
    return user_answer;
}
