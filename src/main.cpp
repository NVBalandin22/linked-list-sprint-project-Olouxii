#include <iostream>
#include <chrono>
using namespace std;
struct Event {
    std::chrono::year_month_day date;
    string name;
    string location;
    string figure;
    string results;
    string description;
    Event* nextEvent;
};

int main() {
    cout << "Welcome to the OlouXii app" << endl;
    void showMainMenu();

}