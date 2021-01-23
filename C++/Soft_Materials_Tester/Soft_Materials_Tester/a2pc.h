#pragma once

#ifndef A2PC_H
#define A2PC_H

//#include <windows.h>
//#include <stdio.h>
//#include <stdlib.h>
#include "SerialPort.h"
#include <string>


void serialWrite(SerialPort arduino, std:: string data);
std::string serialRead(SerialPort arduino);

#endif //A2PC

