#include <chrono>
#include<iostream>
#include "funcs.h"




int showMainMenu() {
    std::cout << "\n======== OlouXii Menu ========\n";
    std::cout << "0 Exit" << std::endl;
    std::cout << "1 Add first event" << std::endl;
    std::cout << "2 Append event" << std::endl;
    std::cout << "3 Add new event and resort list" << std::endl;
    std::cout << "4 Edit event" << std::endl;
    std::cout << "5 Search event by name" << std::endl;
    std::cout << "6 Search event by date" << std::endl;
    std::cout << "7 Delete element" << std::endl;
    std::cout << "8 Show the whole list" << std::endl;
    std::cout << "9 Reports" << std::endl;
    std::cout << "Choose an option: ";

    int user_answer;
    std::cin >> user_answer;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return user_answer;
}

int showReportsMenu() {
    std::cout << "1 Short list" << std::endl;
    std::cout << "2 Events that happened in the same year" << std::endl;
    std::cout << "3 Events with the same key figure" << std::endl;
    std::cout << "Choose an option: ";

    int user_answer;
    std::cin >> user_answer;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return user_answer;
}