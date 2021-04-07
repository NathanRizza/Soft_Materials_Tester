//Nathan Rizza
#include "a2pc.h"

char output[MAX_DATA_LENGTH];
char incomingData[MAX_DATA_LENGTH];

void serialWrite(SerialPort arduino, std::string data) 
{
	char* charArray = new char[data.size() + 1];
	copy(data.begin(), data.end(), charArray);
	charArray[data.size()] = '\n';

	arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
	Sleep(1000);
	arduino.readSerialPort(output, MAX_DATA_LENGTH);//waits for any responce before moving on
	delete[] charArray;
	return;
}

std::string serialRead(SerialPort arduino) 
{
	std::string outputString = "temp";
	arduino.readSerialPort(output, MAX_DATA_LENGTH);
	outputString = output;
	return outputString;
}

bool isConnectedMenu(SerialPort arduino)
{
	if (arduino.isConnected()) //Pretend that we have a connection
	{
		std::cout << "Connection is Established" << std::endl;
		return(true);
	}
	else
	{
		std::cout << "Error connecting to the arduino" << std::endl;
		return(false);
	}
}