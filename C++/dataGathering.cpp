#include "dataGathering.h"

void getData(SerialPort dataArduino)
{
	float forceValues[10000];
	int j = 0;
	std::string data = "0";
	bool gather = true;
	data = serialRead(dataArduino);
	data = "0";
	while (gather)
	{
		data = serialRead(dataArduino);
		if (data.find('d')>0 || j==999)
		{
			break;
		}
		forceValues[j] = std::stof(data);
		Sleep(100);
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
		std::ofstream outfile(fileName + ".txt");

		for (int i = 0; i < j; i++)
		{
			outfile << i << ',' << forceValues[i] << std::endl;
		}
		outfile.close();
		std::cout << "Data saved to file: " + fileName + ".txt " << std::endl;
		system("pause");
		return;
}