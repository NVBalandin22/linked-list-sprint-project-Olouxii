#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <chrono>

struct Event {
    std::chrono::year_month_day date;
    std::string name;
    std::string location;
    std::string figure;
    std::string results;
    std::string description;
    Event* nextEvent;

    Event(std::chrono::year_month_day d, std::string n, std::string loc,
          std::string fig, std::string res, std::string desc);
};

#endif //EVENT_H