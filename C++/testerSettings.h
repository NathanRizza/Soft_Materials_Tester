#pragma once
#include "customTests.h"
#include <string>

#ifndef TESTERSETTINGS_H
#define TESTERSETTINGS_H

void setMaxSpeed();
void setMaxDistance();
void setMaxAcceleration();
void setSamplesPerSecond(SerialPort dataArduino);
void setConversionFactor();

int getMaxSpeed();
int getMaxDistance();
int getMaxAcceleration();
int getSamplesPerSecond();
float getConversionFactor();

void readSettingsFromFile(SerialPort dataArduino);
void writeSettingsToFile();
void setdefaultSettings(SerialPort dataArduino);
void showSettings();

#endif //TESTERSETTINGS_H