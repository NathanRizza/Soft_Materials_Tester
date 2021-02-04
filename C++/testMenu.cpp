#include "testMenu.h"

void TestLibrary(SerialPort controlArduino, SerialPort dataArduino)
{
	while (true)
	{
		std::cout << "\033[2J\033[1;1H"; // Clear consul
		std::cout << "What test would you like to run?" << std::endl;
		std::cout << "(1): Tensile Test" << std::endl;
		std::cout << "(2): Compression Test" << std::endl;
		std::cout << "(3): Adhesion Test" << std::endl;
		std::cout << "(4): Creep Test" << std::endl;
		std::cout << "(5): Stress Relaxation Test" << std::endl;
		std::cout << "(6): Run Custom Test" << std::endl;
		std::cout << "(0): Back to Main Menu" << std::endl;

		std::string userInput = "9";
		std::cin >> userInput;
		std::cout << "\033[2J\033[1;1H";

		if (userInput == "0")
		{
			return;
		}
		else if (userInput == "1")
		{
			tensileTest(controlArduino, dataArduino);
			system("pause");
		}
		else if (userInput == "2")
		{
			compressionTest();
		}
		else if (userInput == "3")
		{
			adhesionTest();
		}
		else if (userInput == "4")
		{
			creepTest();
		}
		else if (userInput == "5")
		{
			StressRelaxationTest();
		}
		else if (userInput == "6")
		{
			runCustomTest();
		}
		else
		{
			std::cout << "Invalid input try again." << std::endl;
			system("pause");
		}
		std::cout << "\033[2J\033[1;1H";
	}
}


void tensileTest(SerialPort controlArduino, SerialPort dataArduino)
{
	bool done = true;
	float matLength = 0;
	float matWidth = 0;
	float matThickness = 0;
	float distanceCM = 0;
	float velocityCM = 0;
	float accCM = 0;
	int disPulse = 0;
	int velPulse = 0;
	int accPulse = 0;
	std::string disString = "d";
	std::string velString = "v";
	std::string accString = "a";
	while (done)
	{
		std::cout << "Tensile Test Menu:" << std::endl;
		//Temp removed untill data collection system is online
		//std::cout << "Enter the Length of the Material in (mm)" << std::endl;
		//std::cin >> matLength;
		//std::cout << "Enter the Width of the Material in (mm)" << std::endl;
		//std::cin >> matWidth;
		//std::cout << "Enter the Thickness of the Material in (mm)" << std::endl;
		//std::cin >> matThickness;

		std::cout << "How far would you like the Tester to pull in addition to the current displacement? (cm)" << std::endl;
		std::cin >> distanceCM;
	

		std::cout << "Velocity of the Tester? (cm/s)" << std::endl;
		std::cin >> velocityCM;


		std::cout << "Acceleration of the Tester? (cm/s)" << std::endl;
		std::cin >> accCM;


		disPulse = distanceCM * (1600 / 0.3);
		velPulse = velocityCM * (1600 / 0.3);
		accPulse = accCM *(1600/0.3);
		disString = std::to_string(disPulse);
		velString = std::to_string(velPulse);
		accString = std::to_string(accPulse);

		std::cout << std::endl;
		std::cout << "Distance(Pulses): "<< disString << std::endl;
		std::cout << "Velocity(Pulses/sec): "<< velString << std::endl;
		std::cout << "Acceleration(Pulses/sec^2): "<< accString << std::endl;


		std::cout << std::endl;
		std::cout << "(1): Perform Test" << std::endl;
		std::cout << "(2): Re-enter Test" << std::endl;
		std::cout << "(3): Exit without Performing Test" << std::endl;

		std::string confirmedString = "0";
		while (confirmedString != "1" && confirmedString != "2" && confirmedString != "3")
		{
			std::cin >> confirmedString;

			if (confirmedString == "1")
			{
				done = false;
				//Run test


			}
			else if (confirmedString == "2")
			{

			}
			else if (confirmedString == "3")
			{
				return;
			}
			else
			{
				std::cout << "Invalid input try again." << std::endl;
				system("pause");
			}

		}
		std::cout << "\033[2J\033[1;1H";
	}
	
	std::cout << "Sending test to arduino, please wait..."<< std::endl;
	serialWrite(controlArduino, "t");
	serialWrite(controlArduino, disString);
	serialWrite(controlArduino, velString);
	serialWrite(controlArduino, accString);
	std::cout << "Test Sent!" << std::endl;
	
	return;
}

void compressionTest()
{

}

void adhesionTest()
{

}

void creepTest()
{

}

void StressRelaxationTest()
{

}

void runCustomTest()
{

}