#include <iostream>
#include <chrono>
#include<EventFunctions.h>
#include<funcs.h>
using namespace std;
int showMainMenu() {
    cout << "1 Search event by name" << endl << "2 Add first event" << endl << "3 Append event" << endl << "4 Add new event and resort list" << endl << "5 Edit event" << endl << "6 Search event by date" << endl << "7 Delete element" << endl;
    int user_answer;
    cin >> user_answer;
    return user_answer;

}

int main() {
    Event* head = nullptr;
    cout << "Welcome to the OlouXii app" << endl;
    int userA =  showMainMenu();
    switch (userA) {
        case 1: {
            //Event* searched = searchByName();
        };
    }
}