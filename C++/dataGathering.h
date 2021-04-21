//Nathan Rizza
#pragma once

#ifndef DATAGATHERING_H
#define DATAGATHERING_H

#include <windows.h>
#include "a2pc.h"
#include "customTests.h"

void getData(SerialPort dataArduino, std::string fileName, int velPulse, int accPulse); // For tensile ect...
void getDataNoDistance(SerialPort dataArduino, std::string fileName);
void getCreepTestData(SerialPort controlArduino, std::string fileName);
std::string getValidFileName();
void flushArduinos(SerialPort dataArduino, SerialPort controlArduino);
void flushArduinos(SerialPort dataArduino);
float calcPosition(float time, int velPulse, int accPulse);


#endif //DATAGATHERING