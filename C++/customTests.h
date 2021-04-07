//Nathan Rizza
#pragma once

#include "test.h"
#include <filesystem>
#include <fstream>
#include "a2pc.h"


#ifndef CUSTOMTESTS_H
#define CUSTOMTESTS_H

void runCustomTest(SerialPort controlArduino,test customTest);
void MakeCustomTest();
void manageCustomTests();
void viewAllCustomTests();
void deleteCustomTest(std::string filename);
bool canOpenFile(std::string filename);
bool doesFileExist(std::string fullFileName);
void writeTestToFile(test printTest);
void printTestToScreen(test printTest);
test readTestFromFile(std::string filename);
void viewSpecificTest();
void maxSpeedCheck(int& pulsePerSec);
void maxDistanceCheck(int& distance);
void maxAccelerationCheck(int& acc);
void checkAll(int& pulsePerSec, int& distance,int& acc);
int cmToPulse(float cm);
float pulseToCM(int pulse);

#endif //CUSTOMTESTS_H
