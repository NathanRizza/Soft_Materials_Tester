//Nathan Rizza

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

		//while (dataArduino.isConnected()) 
		//{
		//	std::cout << "Enter your command: " << std::endl;
		//	std::string data;
		//	std::cin >> data;
		//	
		//	serialWrite(dataArduino,data);
		//	std::string output = serialRead(dataArduino);
		//	std::cout << output;
		//}
		//return 0;
}