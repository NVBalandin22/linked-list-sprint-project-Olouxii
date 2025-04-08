#include "EventFunctions.h"
#include <iostream>
#include <chrono>
#include <utility>
#include <filesystem>
#include <fstream>


Event::Event(std::chrono::year_month_day d, std::string n, std::string loc,
             std::string fig, std::string res, std::string desc)
    : date(d), name(std::move(n)), location(std::move(loc)), figure(std::move(fig)), results(std::move(res)), description(std::move(desc)), nextEvent(nullptr) {}       // Initialize all fields using constructor initializer list. std::move is used to avoid unnecessary copying



void createDirectory() { //Function to check if data folder exists
    std::filesystem::path dir = "data";
    if (!exists(dir)) {
        create_directory(dir);
    }
}

void loadEventsFromFile(Event*& head, const std::string& filename) {
    std::ifstream file(filename);       // Open a file for reading
    if (!file) {        // Check if the file exists and opened successfully
        std::cerr << "No saved data found in " << filename << ". Starting with empty list.\n";
        return;
    }

    std::string name, location, figure, results, description, line;
    int year;
    unsigned month, day;        // Variables for storing individual date

    Event* tempHead = nullptr;
    Event** current = &tempHead;

    while (true) {
        file >> year >> month >> day;
        file.ignore(); // Skip the newline character after reading numbers

        if (file.eof()) break;      // If end of file reached, break the loop

        std::getline(file, name);
        std::getline(file, location);
        std::getline(file, figure);
        std::getline(file, results);
        std::getline(file, description);
        std::getline(file, line); // Separator;Read the remaining fields of the event, one line at a time

        *current = new Event({std::chrono::year{year}, std::chrono::month{month}, std::chrono::day{day}},
                             name, location, figure, results, description); // Create a new Event object
        current = &((*current)->nextEvent);
    }

    head = tempHead; // Set the head of the actual list to the built temporary list
}

void saveEventsToFile(Event* head, const std::string& filename) {
    std::ofstream file(filename); // Open a file for writing
    if (!file) {  // Check if the file was opened successfully
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    Event* current = head;
    while (current) { // Write info to a text file
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
}


void normalizeDate(unsigned& day, unsigned& month, int& year) { // function for correction user's info
    while (true) {  // Check if the current date is valid; if yes, break the loop
        if (std::chrono::year_month_day{
                std::chrono::year{year},
                std::chrono::month{month},
                std::chrono::day{day}
            }.ok()) {
            break;
            }

        std::chrono::year_month ym{std::chrono::year{year}, std::chrono::month{month}};     // Create a year_month object from the given year and month
        unsigned daysInMonth = static_cast<unsigned>(       // Get the number of days in the given month
            std::chrono::year_month_day_last{ym / std::chrono::last}.day()
        );

        int i = static_cast<int>(month);    // Convert month to int

        if (i > 12) { // Normalize month
            year += i / 12;
            i = i % 12;
            if (i == 0) {
                i = 12;
                --year;
            }
        }
        month = static_cast<unsigned>(i);

        if (day > daysInMonth) { //Normalize day
            month += day / daysInMonth;
            day = day % daysInMonth;
            if (day == 0) {
                day = daysInMonth;
                --month;
            }
        }
    }
}

void initializeEvents(Event*& head) { //function to fill the list with meaningless events
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


std::string askLongInput() { //Function to avoid incorrect input
    std::string input;

    while (true) {
        std::getline(std::cin >> std::ws, input);

        if (input.length() < 3) {
            std::cout << "Enter at least 3 symbols:  ";
        } else {
            return input;
        }
    }
}

Event* createEvent() { //Function for new Events.
    unsigned day, month;
    int year;       // Declare variables to store user input for event details.

    std::cout << "Enter event name: ";
    std::string name = askLongInput();

    std::cout << "Enter event location: ";
    std::string location = askLongInput();

    std::cout << "Enter historical figure: ";
    std::string figure = askLongInput();

    std::cout << "Enter results: ";
    std::string results = askLongInput();

    std::cout << "Enter description: ";
    std::string description = askLongInput();

    while (true) { //Incorrect cin protection
        std::cout << "\nEnter event date (DD MM YYYY): ";
        std::cin >> day >> month >> year;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter numeric values.\n";
            continue;
        }
        break;
    }

    normalizeDate(day, month, year);        // Normalize the date in case it is invalid

    std::chrono::year_month_day date{       // Create a chrono date object from the input values
        std::chrono::year{year},
        std::chrono::month{month},
        std::chrono::day{day}
    };

    return new Event(date, name, location, figure, results, description);
}

void sortEventsByDate(Event*& head) { //Function to sort lists
    if (!head || !head->nextEvent) return;      // If the list is empty or has only one element, no need to sort

    bool swapped;
    do {
        swapped = false;
        Event** current = &head;

        while ((*current)->nextEvent) {     //Basic bubble sort
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


Event* addFirst(Event* head) { //New element at the beginning of the list
    Event *newEvent = createEvent();
    newEvent->nextEvent = head;     // Link the new event to the current head
    return newEvent;
}

Event* addLast(Event* head) {       //New element at the end of the list
    Event *newEvent = createEvent();
    if (!head) return newEvent; // If the list is empty, the new event becomes the head
    Event* curr = head;
    while (curr->nextEvent) {       // Traverse to the last element of the list
        curr = curr->nextEvent;
    }
    curr->nextEvent = newEvent;
    return head;
}

Event* addSortedByDate(Event* head) {
    head = addFirst(head); //New element at the beginning of the list
    sortEventsByDate(head); // Sort the entire list
    return head;
}



Event* searchByDate(Event* head) {
    int year;
    unsigned day, month;
    std::cout << "Enter day, month, year: ";
    std::cin >> day >> month >> year;   // Prompt user to input the date
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); std::cin >> month >> year;// Ignore any leftover characters from the input buffer
    auto searchDate = std::chrono::year_month_day{std::chrono::year{year}, std::chrono::month{month}, std::chrono::day{day}};       // Create a chrono-compatible date for comparison

    Event* curr = head;
    while (curr) {      // Traverse the list to find an event with the same date
        if (curr->date == searchDate) {
            return curr;
        }
        curr = curr->nextEvent;
    }
    std::cout << "\033[1;31mEvent not found for this date.\033[0m\n"; // Print red-colored message if event is not found

    return nullptr;
}

Event* searchByName(Event* head) {
    std::string searchName;
    std::cout << "Enter Event name: ";
    std::getline(std::cin, searchName);     // Ask user to input the name of the event

    Event* curr = head;
    while (curr) {
        if (curr->name == searchName) {     // Traverse the list and compare names
            return curr;
        }
        curr = curr->nextEvent;
    }
    std::cout << "Event not found with name: " << searchName << "\n";
    return nullptr;
}

void searchEventsByYear(const Event* head) { //Find events that happened in the same year
    int year;
    std::cout << "Enter year: ";
    std::cin >> year;       // Ask the user to enter a year

    bool found = false;     // A flag
    const Event* current = head;
    while (current) {       // Traverse the list and print every event with a matching year
        if (static_cast<int>(current->date.year()) == year) {
            printEvent(current);
            found = true;
        }
        current = current->nextEvent;
    }

    if (!found) {
        std::cout << "\033[1;31mNo events found for year " << year << ".\033[0m\n";     // If no events matched, print a red error message
    }
}

void searchEventsByFigure(const Event* head) {
    std::string figure;
    std::cout << "Enter figure: ";
    std::getline(std::cin >> std::ws, figure);      // Prompt the user to enter the name of a participant

    bool found = false;     // Flag
    const Event* current = head;
    while (current) {       // Traverse the event list and print any event where the figure matches
        if (current->figure == figure) {
            printEvent(current);
            found = true;
        }
        current = current->nextEvent;
    }

    if (!found) {
        std::cout << "\033[1;31mNo events found for figure: " << figure << ".\033[0m\n";
    }
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

void printEvent(const Event* e) {       // Prints detailed information about a single event.
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

        void printFullList(const Event* head) {     // Prints the full list of events with detailed information.
    const Event* current = head;
    while (current) {
        printEvent(current);
        current = current->nextEvent;
    }
    std::cout << "----------------------------------\n";
}


void editEvent(Event*& event) {
    Event* oldEvent = searchByName(event);      // Search for the event to edit

    if (!oldEvent) return;      // If not found, exit

    Event* newEvent = createEvent();        // Create a new event with new data
    Event* temp = event;

    while (temp) {
        if (temp == oldEvent) {
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
    printEvent(temp);        // Print the event
    delete newEvent;        // Clean up dynamically allocated memory
}

Event* deleteEvent(Event* head) {
    Event* eventToDelete = searchByName(head);

    if (!head || !eventToDelete) return head;       // If list is empty or event not found, return the original list unchanged

    if (head == eventToDelete) {
        Event* temp = head;
        head = head->nextEvent;
        delete temp;
        return head;
    }

    Event* curr = head;
    while (curr->nextEvent && curr->nextEvent != eventToDelete) { //Delete middle element
        curr = curr->nextEvent;
    }

    if (curr->nextEvent) { //Not nullptr
        Event* temp = curr->nextEvent;
        curr->nextEvent = curr->nextEvent->nextEvent;
        delete temp;
    }
    std::cout << "Deleted" << "\n";
    return head;
}