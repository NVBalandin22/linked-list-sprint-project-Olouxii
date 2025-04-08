#include <chrono>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <algorithm>
#include "funcs.h"


std::string toLower(const std::string& str) {
    std::string res = str;
    std::ranges::transform(res, res.begin(), ::tolower);
    return res;
}

std::string chooseTopic() {
    namespace fs = std::filesystem;
    std::string topic;
    std::cout << "Enter topic (press Enter for default): ";
    std::getline(std::cin, topic);

    if (topic.empty()) {
        return "../data/events.txt";
    }

    topic = toLower(topic);
    std::string filepath = "../data/" + topic + ".txt";

    if (!fs::exists(filepath)) {
        std::cout << "File for topic doesn't exist. Create new? (y/n): ";
        char choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 'y' || choice == 'Y') {
            std::ofstream file(filepath);
            if (!file) {
                std::cerr << "Failed to create file: " << filepath << "\n";
                return "../data/events.txt";
            }
            file.close();
            std::cout << "File created: " << filepath << "\n";
        } else {
            return "../data/events.txt";
        }
    }

    return filepath;
}


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
    std::cout << "0 Exit" << std::endl;
    std::cout << "1 Short list" << std::endl;
    std::cout << "2 Events that happened in the same year" << std::endl;
    std::cout << "3 Events with the same key figure" << std::endl;
    std::cout << "Choose an option: ";

    int user_answer;
    std::cin >> user_answer;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return user_answer;
}