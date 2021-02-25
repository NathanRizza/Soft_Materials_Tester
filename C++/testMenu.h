//you might be able to get all dependancies when including this header
#pragma once

#include "customTests.h"//uses test and testStep
#include "a2pc.h" //Uses SerialPort
#include "dataGathering.h"

#ifndef TESTMENU_H
#define TESTMENU_H

void TestLibrary(SerialPort controlArduino, SerialPort dataArduino);
void tensileTest(SerialPort controlArduino, SerialPort dataArduino);
void compressionTest();
void adhesionTest();
void creepTest();
void StressRelaxationTest();
void runCustomTest(SerialPort controlArduino, SerialPort dataArduino);

#endif //TESTMENU