#ifndef FUNCS_H
#define FUNCS_H
#include "Event.h"

void listTxtFiles(const std::string& folderPath);

std::string chooseTopic();

void initializeEvents(Event*& head);

int showMainMenu();

int showReportsMenu();

#endif //FUNCS_H
