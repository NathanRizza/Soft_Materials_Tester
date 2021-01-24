#pragma once
#include "testMenu.h"

#ifndef USERMENU_H
#define USERMENU_H

void mainMenu(SerialPort controlArduino, SerialPort dataArduino);
void settings();
void help();
//void dataOutput(int time[], int distance[], int force[]);

#endif//USERMENU_H