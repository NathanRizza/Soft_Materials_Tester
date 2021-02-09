/* Zain Ul Mustafa 2017 */

//Rules:
/*
1. Check if connection with Arduino is made
2. If Arduino is connected then take input from user in a String
3. Make a char array of the size of string + 1
4. Copy the whole string into the char array
5. Add escape sequence \n because this represents the end of a line in Serial Comm port
6. Write the whole char array into the buffer (a buffer takes the info forward to the Serial Comm Port)
7. Read from the Arduino if data is received successfully or if the action is taken as per needed
*/

//Connect with me:
/*	Twitter: http://www.twitter.com/ZainsOfficial/
	Facebook: http://www.facebook.com/ZainsOfficial/
	Github: http://github.com/ZainUlMustafa/
*/

/* This software is allowed for any user to copy, modify, merge, and distribute in any of his/her project.
Complete repository for this project is available on github. If you find this project anywhere except github, it
is to be noted that it is not made by me and not distributed by me. 
Please follow this link to get to the original repository of github for this project
Github shortened link (no spam and no ads): http://bit.ly/2vGkinQ
*/

#include "userMenu.h"
//userMenu has the following dependancies:
//iostream
//filesystem
//stream
//string
//All personally written header Files


char commport1[] = "\\\\.\\COM3"; //commport1 is the controlArduino which drives the motors.
char* port1 = commport1;
char commport2[] = "\\\\.\\COM4"; //commport2 is the DataArduino which sends data to the PC.
char* port2 = commport2;

int main()
{
	SerialPort controlArduino(port1); 
	SerialPort dataArduino(port2);
	Sleep(1000);
	if (isConnectedMenu(controlArduino)) 
	{
		mainMenu(controlArduino,dataArduino);
	}

		while (dataArduino.isConnected()) 
		{
			std::cout << "Enter your command: " << std::endl;
			std::string data;
			std::cin >> data;
			
			serialWrite(dataArduino,data);
			std::string output = serialRead(dataArduino);
			std::cout << output;
		}
		return 0;
}