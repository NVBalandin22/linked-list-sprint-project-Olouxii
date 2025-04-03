#include <iostream>
#include <chrono>
#include<EventFunctions.h>
#include<funcs.h>
using namespace std;
int showMainMenu() {
    cout << "1 Add first event" << endl << "2 Append event" << endl << "3 Add new event and resort list" << endl << "4 Edit event" << endl << "5 Search event by name" << endl << "6 Search event by date" << endl << "7 Delete element" << endl;
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

        };
    }
}