#include <chrono>
#include<iostream>
#include "funcs.h"

using namespace std;



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
    cout << "8 Show the whole list" << endl;
    cout << "Choose an option: ";

    int user_answer;
    cin >> user_answer;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return user_answer;
}
