#pragma once

#ifndef A2PC_H
#define A2PC_H

#include "SerialPort.h"
#include <string>
#include <iostream>
#include "testerSettings.h"


void serialWrite(SerialPort arduino, std:: string data);
std::string serialRead(SerialPort arduino);
bool isConnectedMenu(SerialPort arduino);

#endif //A2PC

