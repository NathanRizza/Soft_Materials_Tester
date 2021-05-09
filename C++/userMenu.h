//Nathan Rizza
#pragma once
#include "testMenu.h"

#ifndef USERMENU_H
#define USERMENU_H

void mainMenu(SerialPort controlArduino, SerialPort dataArduino);
void settings(SerialPort dataArduino);
void help();

#endif//USERMENU_H