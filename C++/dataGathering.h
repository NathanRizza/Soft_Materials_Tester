#pragma once

#ifndef DATAGATHERING_H
#define DATAGATHERING_H

#include <windows.h>
#include "a2pc.h"
#include "customTests.h"

void getData(SerialPort dataArduino, std::string fileName);
std::string getValidFileName();
void writeData(std::ofstream outfile, float data);
void flushArduinos(SerialPort dataArduino, SerialPort controlArduino);
void flushArduinos(SerialPort dataArduino);


#endif //DATAGATHERING