//Nathan Rizza
#include "dataGathering.h"
#include <ctime>
#include <ratio>
#include <chrono>

void getData(SerialPort dataArduino,std::string fileName, int velPulse, int accPulse)
{
	float time = 0;
	float chronoTime = 0;
	float forceValue = 0;
	float sampleRateFloat = getSamplesPerSecond();
	std::string data = "0";
	std::ofstream outfile(fileName + ".csv"); //"/testData/"+ ?
	std::cout << "Data Collection has started" << std::endl;
	outfile << "Time (sec)" << "," << "Distance (CM)" << "," <<"Force (N)" << "\n";
	Sleep(1000);
	flushArduinos(dataArduino);
	while (true)
	{
		std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
		data = serialRead(dataArduino);
		if (data.find('d') != std::string::npos)
		{
			break;
		}
		forceValue = std::stof(data);
		forceValue = (forceValue/getConversionFactor());
		
		outfile << (truncf(time*100)/100) << ',' << calcPosition(time, velPulse, accPulse) << ',' << forceValue << std::endl;
		do
		{
			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> time_span = t2 - t1;
			chronoTime = time_span.count();
		} while (chronoTime < ((1000 / (sampleRateFloat)-1)));
		//Sleep((958 / getSamplesPerSecond())-1);
		time = time+(1.0/getSamplesPerSecond());
	}
	std::cout << "Data saved to file: " + fileName + ".csv " << std::endl;
	return;
}

void getDataNoDistance(SerialPort dataArduino, std::string fileName)
{
	float time = 0;
	float forceValue = 0;
	std::string data = "0";
	std::ofstream outfile(fileName + ".csv"); //"/testData/"+ ?
	std::cout << "Data Collection has started" << std::endl;
	outfile << "Time (sec)" << "," << "Force (N)" << "\n";
	flushArduinos(dataArduino);
	while (true)
	{
		data = serialRead(dataArduino);
		if (data.find('d') != std::string::npos)
		{
			break;
		}
		forceValue = std::stof(data);
		forceValue = (forceValue / getConversionFactor());

		outfile << (truncf(time * 10) / 10) << ',' << forceValue << std::endl;
		Sleep((978 / getSamplesPerSecond()) - 1);
		time = time + (1.0 / getSamplesPerSecond());
	}
	std::cout << "Data saved to file: " + fileName + ".csv " << std::endl;
	return;
}

void getDataStressRelax(SerialPort dataArduino, std::string fileName, int velPulse, int accPulse, int disPulse) 
{
	float time = 0;
	float distance = 0;
	float forceValue = 0;
	std::string data = "0";
	std::ofstream outfile(fileName + ".csv"); //"/testData/"+ ?
	std::cout << "Data Collection has started" << std::endl;
	outfile << "Time (sec)" << "," << "Force (N)" << "," << "Distance (CM)" << "\n";
	flushArduinos(dataArduino);
	while (true)
	{
		data = serialRead(dataArduino);
		if (data.find('d') != std::string::npos)
		{
			break;
		}
		forceValue = std::stof(data);
		forceValue = (forceValue / getConversionFactor());

		if (calcPosition(time, velPulse, accPulse) > pulseToCM(disPulse))
		{
			distance = pulseToCM(disPulse);
		}
		else 
		{
			distance = calcPosition(time, velPulse, accPulse);
		}

		outfile << (truncf(time * 10) / 10) << ',' << forceValue << ',' << distance << std::endl;
		Sleep((978 / getSamplesPerSecond()) - 1);
		time = time + (1.0 / getSamplesPerSecond());
	}
	std::cout << "Data saved to file: " + fileName + ".csv " << std::endl;
	return;
}


void getCreepTestData(SerialPort controlArduino, std::string fileName) 
{
	float time = 0;
	float distancePulses = 0;
	std::string data = "0";
	std::ofstream outfile(fileName + ".csv"); //"/testData/"+ ?
	std::cout << "Data Collection has started" << std::endl;
	outfile << "Time (sec)" << "," << "Distance (cm)" << "\n";
	flushArduinos(controlArduino);
	while (true)
	{
			data = serialReadUntillAvailable(controlArduino);

		if (data.find('d') != std::string::npos)
		{
			break;
		}
		distancePulses = std::stof(data);
		outfile << time << ',' << pulseToCM(distancePulses) << std::endl;
	}
	std::cout << "Data saved to file: " + fileName + ".csv " << std::endl;
	return;
}

std::string getValidFileName()
{
	std::string fileName = "";
	std::cout << "Name the file that the data will be saved to. (One word, no spaces)" << std::endl;
	std::cin >> fileName;

	while (doesFileExist(fileName))
	{
		std::cout << "\033[2J\033[1;1H";
		std::cout << "A Test Named " << fileName << " alreadyExists, try another name." << std::endl;
		std::cin >> fileName;
	}
	return fileName;
}

void flushArduinos(SerialPort arduino1, SerialPort arduino2) 
{
	std::string temp = "";
	Sleep(100);
	temp = serialRead(arduino2);
	temp = serialRead(arduino1);
}

void flushArduinos(SerialPort arduino) 
{
	std::string temp = "";
	Sleep(100);
	temp = serialRead(arduino);
}

float calcPosition(float time, int velPulse, int accPulse) 
{
	float velPulseFloat = velPulse;
	float accPulseFloat = accPulse;
	float disPulse = 0;
	float firstLegTime = 0;
	if (accPulse > 0) 
	{
		if ((accPulseFloat * time) < velPulse) 
		{
			disPulse = 0.5 * accPulseFloat * time * time;
		}
		else 
		{
			firstLegTime = accPulseFloat / velPulseFloat;
			disPulse = 0.5 * accPulseFloat * firstLegTime * firstLegTime;
			disPulse = disPulse + (velPulseFloat*(time-firstLegTime));
		}
	}
	else 
	{
		disPulse = velPulseFloat * time;
	}
	return pulseToCM(disPulse);
}