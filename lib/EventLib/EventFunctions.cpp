#include "EventFunctions.h"
#include <iostream>
#include <chrono>
#include <utility>

#include <fstream>


//#include <chrono>

std::string askLongInput() {
    std::string input;
    std:: cout << "Enter information at least 3 symbols: ";

    while (true) {
        getline(std::cin, input);

        if (input.length() < 5) {
            std::cout << "Enter at least 3 symbols ";
        } else {
            return input;
        }
    }
}


void normalizeDate(unsigned& day, unsigned& month, int& year) {
    while (true) {      // Check if the current date is valid; if yes, break the loop
        if (std::chrono::year_month_day{
                std::chrono::year{year},
                std::chrono::month{month},
                std::chrono::day{day}
            }.ok()) {
            break;
            }

        std::chrono::year_month ym{std::chrono::year{year}, std::chrono::month{month}}; // Create a year_month object from the given year and month
        unsigned daysInMonth = static_cast<unsigned>(     // Get the number of days in the given month
            std::chrono::year_month_day_last{ym / std::chrono::last}.day()
        );

        int i = static_cast<int>(month); // Convert month to int for further manipulation

        if (i > 12) {   // If month > 12, add extra months as full years
            year += i / 12;
            i = i % 12;   // Get remaining months after converting to years
            if (i == 0) {   // Adjust for edge case when i == 0: set to December and subtract one year
                i = 12;
                --year;
            }
        }
        month = static_cast<unsigned>(i);  // Set the normalized month value

        if (day > daysInMonth) {
            month += day / daysInMonth;  // If day exceeds days in current month, add overflow to month
            day = day % daysInMonth;  // Keep only the remaining days
            if (day == 0) {  // If remainder is 0, set day to last day of previous month and adjust month
                day = daysInMonth;
                --month;
            }
        }
    }
}



void initializeEvents(Event*& head) {
    head = new Event({std::chrono::year{2024}, std::chrono::month{5}, std::chrono::day{10}},
                     "Conference", "New York", "Dr. Smith", "Success", "Annual Tech Conference"); // Create the first Event node

    head->nextEvent = new Event({std::chrono::year{2023}, std::chrono::month{11}, std::chrono::day{20}},
                                "Workshop", "San Francisco", "Jane Doe", "Completed", "AI Workshop"); // Link the second event to the first one

    head->nextEvent->nextEvent = new Event({std::chrono::year{2022}, std::chrono::month{7}, std::chrono::day{15}},
                                           "Hackathon", "Berlin", "John Connor", "Winners Announced", "48-hour coding challenge");

    head->nextEvent->nextEvent->nextEvent = new Event({std::chrono::year{2025}, std::chrono::month{1}, std::chrono::day{5}},
                                                      "Startup Meetup", "London", "Elon Musk", "In Progress", "Networking event for startups");

    head->nextEvent->nextEvent->nextEvent->nextEvent = new Event({std::chrono::year{2023}, std::chrono::month{9}, std::chrono::day{30}},
                                                                 "Product Launch", "Tokyo", "CEO of Sony", "Launched", "New PlayStation release");

    sortEventsByDate(head); // Sort the linked list of events chronologically
}

void saveEventsToFile(Event* head) {
    std::ofstream file("events.txt"); // Open a file named "events.txt" for writing
    if (!file) {    // Check if the file was opened successfully; if not, show an error and exit
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    Event* current = head;  // Create a pointer to iterate through the linked list
    while (current) {
        file << static_cast<int>(current->date.year()) << " "
             << static_cast<unsigned>(current->date.month()) << " "
             << static_cast<unsigned>(current->date.day()) << "\n"   // Write the date (year, month, day) to the file, each value separated by space
             << current->name << "\n"   // Write the name of the event
             << current->location << "\n"  // Write the location of the event
             << current->figure << "\n"  // Write the key figure or speaker
             << current->results << "\n" // Write the results or status of the event
             << current->description << "\n"  // Write a description of the event
             << "---\n";  // Write a separator line to distinguish events
        current = current->nextEvent;  // Move to the next event in the list
    }

    file.close(); // Close the file after writing all events
}

void loadEventsFromFile(Event*& head) {
    std::ifstream file("events.txt"); // Open the file "events.txt" for reading
    if (!file) {    // Check if the file exists and opened successfully; if not, print a message and exit
        std::cerr << "No saved data found, starting with an empty list." << std::endl;
        return;
    }

    std::string name, location, figure, results, description, line;
    int year;
    unsigned month, day;  // Variables for storing individual event fields read from the file

    Event* tempHead = nullptr; // Temporary head for building the list
    Event** current = &tempHead; // Pointer to pointer: used to add new events to the end of the list

    while (true) {
        file >> year >> month >> day; // Read the date: year, month, day
        file.ignore(); // Skip the newline character after reading numbers

        if (file.eof()) break; // If end of file reached, break the loop

        std::getline(file, name);
        std::getline(file, location);
        std::getline(file, figure);
        std::getline(file, results);
        std::getline(file, description);
        std::getline(file, line);    // Read the remaining fields of the event, one line at a time

        *current = new Event({std::chrono::year{year}, std::chrono::month{month}, std::chrono::day{day}},  // Create a new Event object with the read data and store it at *current
                             name, location, figure, results, description);
        current = &((*current)->nextEvent); // Move to the next pointer for the next event
    }

    head = tempHead;  // Set the head of the actual list to the built temporary list
    file.close();
}


Event::Event(std::chrono::year_month_day d, std::string n, std::string loc,
             std::string fig, std::string res, std::string desc)
    : date(d), name(std::move(n)), location(std::move(loc)), figure(std::move(fig)), results(std::move(res)), description(std::move(desc)), nextEvent(nullptr) {} // Initialize all fields using constructor initializer list. std::move is used to avoid unnecessary copying

Event* createEvent() {
    std::string name, location, figure, results, description;
    unsigned day, month;
    int year;  // Declare variables to store user input for event details

    std::cout << "Enter event name: ";
    std::getline(std::cin >> std::ws, name); // Read the name of the event, trimming leading whitespace

    std::cout << "Enter event location: ";
    std::getline(std::cin >> std::ws, location); // Read the location of the event

    std::cout << "Enter historical figure: ";
    std::getline(std::cin >> std::ws, figure); // Read the historical figure associated with the event

    std::cout << "Enter results: ";
    std::getline(std::cin >> std::ws, results); // Read the outcome or result of the event

    std::cout << "Enter description: ";
    std::getline(std::cin >> std::ws, description); // Read the description of the event

    std::cout << "Enter event date (DD MM YYYY): ";
    std::cin >> day >> month >> year; // Read the date of the event from user as day, month, year

    normalizeDate(day, month, year); // Normalize the date in case it is invalid (e.g., 35th day or 15th month)

    std::chrono::year_month_day date{  // Create a chrono date object from the input values
        std::chrono::year{year},
        std::chrono::month{month},
        std::chrono::day{day}
    };

    return new Event(date, name, location, figure, results, description);  // Return a pointer to a newly created Event with the filled-in data
}



void sortEventsByDate(Event*& head) {
    if (!head || !head->nextEvent) return; // If the list is empty or has only one element, no need to sort

    bool swapped;
    do {
        swapped = false;    // Assume no swaps will be needed in this pass
        Event** current = &head; // swaps nodes in a singly linked list

        while ((*current)->nextEvent) {
            if ((*current)->date > (*current)->nextEvent->date) {  // Compare dates of the current node and the next node

                Event* temp = (*current)->nextEvent;
                (*current)->nextEvent = temp->nextEvent;
                temp->nextEvent = *current;
                *current = temp;   // Swap the two adjacent nodes by manipulating pointers
                swapped = true;  // Set flag to true since a swap was made
            }
            current = &((*current)->nextEvent);   // Move to the next node (by reference)
        }
    } while (swapped);  // Repeat the process as long as any swaps occurred in the previous pass
}

Event* addFirst(Event* head) {
    Event *newEvent = createEvent(); // Create a new event based on user input
    newEvent->nextEvent = head; // Link the new event to the current head of the list
    return newEvent; // Return the new event as the new head
}

Event* addLast(Event* head) {
    Event *newEvent = createEvent(); // Create a new event from user input
    if (!head) return newEvent;  // If the list is empty, the new event becomes the head
    Event* curr = head;
    while (curr->nextEvent) { // Traverse to the last element of the list
        curr = curr->nextEvent;
    }
    curr->nextEvent = newEvent; // Link the last node to the new event
    return head; // Return the original head of the list
}

Event* addSortedByDate(Event* head) {
    head = addFirst(head); // Add the new event to the beginning of the list
    sortEventsByDate(head); // Sort the entire list by event date to maintain order

    return head; // Return the updated list head
}


void editEvent(Event*& event) {
    Event* oldEvent = searchByName(event); // Search for the event to edit by name

    if (!oldEvent) return; // If the event was not found, exit

    Event* newEvent = createEvent(); // Create a new event from user input to use as updated data
    Event* temp = event;  // Start from the beginning of the list

    while (temp) {
        if (temp == oldEvent) { // Found the event to be edited
            // Swap the values of the events
            temp->date = newEvent->date;
            temp->name = newEvent->name;
            temp->location = newEvent->location;
            temp->figure = newEvent->figure;
            temp->results = newEvent->results;
            temp->description = newEvent->description; // Copy all updated fields from newEvent to the old one
            return;
        }
        temp = temp->nextEvent; // Move to the next event in the list
    }
    printEvent(temp);  // Print the (possibly modified) event — though in this context temp is likely null
    delete newEvent; // Clean up dynamically allocated memory
}

Event* searchByDate(Event* head) {

    int year;
    unsigned day, month;
    std::cout << "Enter day, month, year: ";
    std::cin >> day >> month >> year; // Prompt user to input the date
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any leftover characters from the input buffer
    auto searchDate = std::chrono::year_month_day{std::chrono::year{year}, std::chrono::month{month}, std::chrono::day{day}}; // Create a chrono-compatible date for comparison

    Event* curr = head;
    while (curr) {    // Traverse the list to find an event with the same date
        if (curr->date == searchDate) {
            return curr;
        }
        curr = curr->nextEvent;
    }
    std::cout << "\033[1;31mEvent not found for this date.\033[0m\n"; // Print red-colored message if event is not found

    return nullptr; // Return null pointer if no match is found
}


Event* searchByName(Event* head) {
    std::string searchName;
    std::cout << "Enter Event name: ";
    std::getline(std::cin, searchName); // Ask user to input the name of the event

    Event* curr = head;
    while (curr) {                   // Traverse the list and compare names
        if (curr->name == searchName) {
            return curr;
        }
        curr = curr->nextEvent;
    }
    std::cout << "Event not found with name: " << searchName << "\n";     // Print message if no match is found
    return nullptr; // Return null pointer if no event matches
}

void searchEventsByYear(const Event* head) {
    int year;
    std::cout << "Enter year: ";
    std::cin >> year;         // Ask the user to enter a year for the search

    bool found = false;      // A flag to track if any event is found
    const Event* current = head;
    while (current) {             // Traverse the list and print every event with a matching year
        if (static_cast<int>(current->date.year()) == year) {
            printEvent(current);
            found = true;
        }
        current = current->nextEvent;
    }

    if (!found) {                 // If no events matched, print a red error message
        std::cout << "\033[1;31mNo events found for year " << year << ".\033[0m\n";
    }
}

void searchEventsByFigure(const Event* head) {
    std::string figure;
    std::cout << "Enter figure: ";
    std::getline(std::cin >> std::ws, figure); // Prompt the user to enter the name of a historical figure or participant

    bool found = false;    // Flag to check if at least one match is found
    const Event* current = head;
    while (current) {      // Traverse the event list and print any event where the figure matches
        if (current->figure == figure) {
            printEvent(current);
            found = true;
        }
        current = current->nextEvent;
    }

    if (!found) {
        std::cout << "\033[1;31mNo events found for figure: " << figure << ".\033[0m\n"; // Traverse the event list and print any event where the figure matches
    }
}




Event* deleteEvent(Event* head) {
    Event* eventToDelete = searchByName(head);

    if (!head || !eventToDelete) return head;  // If list is empty or event not found, return the original list unchanged

    if (head == eventToDelete) {
        Event* temp = head;
        head = head->nextEvent;
        delete temp;
        return head;
    }

    Event* curr = head;
    while (curr->nextEvent && curr->nextEvent != eventToDelete) {   // Traverse the list to find the node just before the one to delete
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







void printList(const Event* head) {          // Prints a simple list of events with their names and dates.
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

void printFullList(const Event* head) {      // Prints the full list of events with detailed information for each.
    const Event* current = head;
    while (current) {
        printEvent(current);
        current = current->nextEvent;
    }
    std::cout << "----------------------------------\n";
}