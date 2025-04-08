#include <iostream>
#include <chrono>

#include<EventFunctions.h>
#include<funcs.h>



int main() {
    Event* head = nullptr;

    loadEventsFromFile(head);
    std::cout << "Welcome to the OlouXii app!" << std::endl;



    while (true) {
        switch (showMainMenu()) {
            case 0: {
                saveEventsToFile(head);
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
            case 3: {
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
            case 9: {
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
            case -1: {
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