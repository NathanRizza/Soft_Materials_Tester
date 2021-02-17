#include "dataGathering.h"

void getData(SerialPort dataArduino)
{
	float forceValues[10000];
	int j = 0;
	std::string data = "0";
	data = serialRead(dataArduino); //Clear buffer
	data = "0";
	while (true)
	{
		data = serialRead(dataArduino);
		if (data.find('d') != std::string::npos || j==9999)
		{
			break;
		}
		forceValues[j] = std::stof(data);
		Sleep(1000);//Every 10th of a second
		j++;
	}
	std::string fileName = "";
	std::cout << "Name the file that the data will be saved to." << std::endl;
	std::cin >> fileName;

	while (doesFileExist(fileName))
	{
		std::cout << "A Test Named " << fileName << " alreadyExists, try another name." << std::endl;
		std::cin >> fileName;
	}
	writeDataToFile(forceValues, j, fileName);

}

void writeDataToFile(float forceValues[],int j,std::string fileName) 
{
		std::ofstream outfile(fileName + ".csv");//https://www.wikihow.com/Create-a-CSV-File

		outfile << "Time" << "," << "Force" << "\n";

		for (int i = 0; i < j; i++)
		{
			outfile << i << ',' << forceValues[i] << std::endl;
		}
		outfile.close();
		std::cout << "Data saved to file: " + fileName + ".csv " << std::endl;
		return;
}