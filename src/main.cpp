#include <iostream>
#include <chrono>

#include<EventFunctions.h>
#include<funcs.h>



using namespace std;

int main() {
    Event* head = nullptr;

    cout << "Welcome to the OlouXii app!" << endl;

    loadEventsFromFile(head);

    while (true) {
        switch (showMainMenu()) {
            case 0: {
                saveEventsToFile(head);
                cout << "Goodbye!\n";
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
            default: {
                cout << "Invalid input. Please try again.\n";
            }
        }
    }
}