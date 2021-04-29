//Nathan Rizza
#include "testerSettings.h"

int maxSpeed = 2500;
int maxDistance = 100000;
int maxAcceleration = 0;
int samplesPerSecond = 20;
float conversionFactor = 1.886; 

void setMaxSpeed() 
{
	int setSpeed = 2500;
	std::cout << "Enter the new Max Speed of the Tester. Default: 2500 pulses/sec  (int only)" << std::endl;
	std::cin >> setSpeed;
	maxSpeed = setSpeed;
	return;

}
void setMaxDistance() 
{
	int setDistance = 100000;
	std::cout << "Enter the new Max Distance of the Tester. Default: 180000 pulses  (int only)" << std::endl;
	std::cin >> setDistance;
	maxDistance = setDistance;
	return;

}
void setMaxAcceleration() 
{
	int setAcceleration = 0;
	std::cout << "Enter the new Acceleration of the Tester. Default: 10000 pulses (int only)" << std::endl;
	std::cin >> setAcceleration;
	maxAcceleration = setAcceleration;
	return;

}

void setSamplesPerSecond(SerialPort dataArduino)
{
	int setSamplesPerSecond = 10000;
	std::cout << "Enter the new sampleing speed of the Tester. Defualt: 20 samples/sec (int only)" << std::endl;
	std::cin >> setSamplesPerSecond;
	samplesPerSecond = setSamplesPerSecond;
	serialWrite(dataArduino, std::to_string(samplesPerSecond));
	return;

}

void setConversionFactor() 
{
	float setConversionFactor = 1.886;
	std::cout << "Enter the new sampleing speed of the Tester. Defualt: "<< conversionFactor <<"(float)" << std::endl;
	std::cin >> setConversionFactor;
	samplesPerSecond = setConversionFactor;
	return;
}

int getMaxSpeed() 
{
	return maxSpeed;
}
int getMaxDistance() 
{
	return maxDistance;
}
int getMaxAcceleration()
{
	return maxAcceleration;
}
int getSamplesPerSecond() 
{
	return samplesPerSecond;
}
float getConversionFactor() 
{
	return conversionFactor;
}

void readSettingsFromFile(SerialPort dataArduino)
{
	test returnedTest;
	std::ifstream inFile;

	inFile.open("settings");

	inFile >> maxSpeed;
	inFile >> maxDistance;
	inFile >> maxAcceleration;
	inFile >> samplesPerSecond;
	inFile >> conversionFactor;
	serialWrite(dataArduino, std::to_string(samplesPerSecond));
	inFile.close();
	return;

}
void writeSettingsToFile() 
{
		remove("settings");
		std::ofstream outfile("settings");
		outfile << maxSpeed << '\n';
		outfile << maxDistance << '\n';
		outfile << maxAcceleration << '\n';
		outfile << samplesPerSecond << '\n';
		outfile << conversionFactor << '\n';
		outfile.close();
		std::cout << "Settings saved successfully!" << std::endl;
		system("pause");
		return;
}
void setdefaultSettings(SerialPort dataArduino) 
{
	maxSpeed = 2500;
	maxDistance = 100000;
	maxAcceleration = 0;
	samplesPerSecond = 20;
	conversionFactor = 1.886;
	serialWrite(dataArduino, std::to_string(samplesPerSecond));
	std::cout << "Default settings saved successfully!" << std::endl;
	showSettings();
	return;
}

void showSettings() 
{
	std::cout << "Max Distance:		 "<< maxDistance << " Pulses" <<std::endl;
	std::cout << "Max Speed:		 " << maxSpeed << " Pulses/sec" << std::endl;
	std::cout << "Acceleration:		"<< maxAcceleration << " Pulses/sec^2"<<std::endl;
	std::cout << "Sample rate:		 "<< samplesPerSecond << " Samples / Second"<< std::endl;
	std::cout << "Conversion Factor:	 " << conversionFactor << std::endl;
	return;
}
