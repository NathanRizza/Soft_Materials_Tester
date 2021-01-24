#pragma once

#include "test.h"
#include <filesystem>
#include <fstream>  


#ifndef CUSTOMTESTS_H
#define CUSTOMTESTS_H

void runCustomTest();
void MakeCustomTest();
void manageCustomTests();
void viewAllCustomTests();
void deleteCustomTest(std::string filename);
bool canOpenFile(std::string filename);
bool doesFileExist(std::string fullFileName);
void writeTestToFile(test printTest);
std::string printTestStep(testStep i);
void printTestToScreen(test printTest);
test readTestFromFile(std::string filename);


#endif //CUSTOMTESTS_H
