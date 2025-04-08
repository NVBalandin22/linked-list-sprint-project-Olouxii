#include <iostream>
#include <chrono>

#include<EventFunctions.h>
#include<funcs.h>


int main() {
    Event* head = nullptr;
    listTxtFiles("../data");
    std::string filename = chooseTopic(); // Prompt the user to choose a topic, which returns a filename to load data from.

    loadEventsFromFile(head, filename); // Load events from the specified file into the linked list.

    std::cout << "Welcome to the OlouXii app!" << std::endl;

    while (true) {
        switch (showMainMenu()) {
            case 0: {                   // Exit: save the current event list and exit the program.
                saveEventsToFile(head, filename);
                std::cout << "Goodbye!\n";
                return 0;
            }
            case 1: {
                head = addFirst(head);
                printFullList(head);
                break;
            }
            case 2: {
                head = addLast(head);
                printFullList(head);
                break;
            }
            case 3: {                            // Add a new event into the list in sorted order by date.
                head = addSortedByDate(head);
                printFullList(head);
                break;
            }
            case 4: {
                editEvent(head);
                printFullList(head);
                break;
            }
            case 5: {
                printEvent(searchByName(head));
                break;
            }
            case 6: {
                printEvent(searchByDate(head));
                break;
            }
            case 7: {
                head = deleteEvent(head);
                printFullList(head);
                break;
            }
            case 8: {
                printFullList(head);
                break;
            }
            case 9: {                  // Reports submenu: contains additional reports/search features.
                bool inReportsMenu = true;
                while (inReportsMenu) {
                    switch (showReportsMenu()) {
                        case 0: {
                            inReportsMenu = false;
                            break;
                        }
                        case 1: {
                            printList(head);
                            break;
                        }
                        case 2: {
                            searchEventsByYear(head);
                            break;
                        }
                        case 3: {
                            searchEventsByFigure(head);
                            break;
                        }
                        default: {
                            std::cout << "Invalid input. Please try again.\n";
                        }
                    }
                }
                break;
            }
            case -6584: {                 // Hidden/test option: initialize list with preset events.
                initializeEvents(head);
                printFullList(head);
                break;
            }
            default: {
                std::cout << "Invalid input. Please try again.\n";
            }
        }
    }
}