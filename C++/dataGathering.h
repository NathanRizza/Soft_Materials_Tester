#pragma once

#ifndef DATAGATHERING_H
#define DATAGATHERING_H

#include <windows.h>
#include "a2pc.h"
#include "customTests.h"

void getData(SerialPort dataArduino);
void writeDataToFile(float forceValues[], int j, std::string fileName);

#endif //DATAGATHERING