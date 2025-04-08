#include <chrono>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <algorithm>
#include "funcs.h"


void listTxtFiles(const std::string& folderPath = "../data") {
    namespace fs = std::filesystem;

    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) { //Check if path exists, if folder exists
        std::cout << "Directory does not exist: " << folderPath << std::endl;
        return;
    }

    std::cout << "Available topics:\n";
    for (const auto& entry : fs::directory_iterator(folderPath)) { // Use iterator to go through the folder
        if (entry.is_regular_file() && entry.path().extension() == ".txt") { //Check if it's file, not dir
            std::string filename = entry.path().stem().string(); //Take only filename, without .txt
            std::cout << "- " << filename << std::endl;
        }
    }
}

std::string toLower(const std::string& str) {  // Converts a string to lowercase using C++20 ranges and ::tolower
    std::string res = str;
    std::ranges::transform(res, res.begin(), ::tolower);
    return res;
}

std::string chooseTopic() {       // Prompts the user to choose a topic, and constructs a filename based on the input.
    namespace fs = std::filesystem;
    std::string topic;
    std::cout << "Enter topic (press Enter for default): ";
    std::getline(std::cin, topic);

    if (topic.empty()) {
        return "../data/events.txt";
    }

    topic = toLower(topic);  // Convert topic name to lowercase to ensure consistent filenames
    std::string filepath = "../data/" + topic + ".txt";  // Build full file path using the topic

    if (!fs::exists(filepath)) {  // Check if the file exists. If not, prompt user for creation.
        std::cout << "File for topic doesn't exist. Create new? (y/n): ";
        char choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear any leftover input after reading one character

        if (choice == 'y' || choice == 'Y') {
            std::ofstream file(filepath); // Try to create the file
            if (!file) {
                std::cerr << "Failed to create file: " << filepath << "\n";
                return "../data/events.txt";
            }
            file.close(); // Close the file after creating it
            std::cout << "File created: " << filepath << "\n";
        } else {
            return "../data/events.txt";
        }
    }

    return filepath;
}


int showMainMenu() {        // Displays the main menu of the OlouXii application.
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



int showReportsMenu() {      // Displays the reports submenu of the OlouXii application.
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