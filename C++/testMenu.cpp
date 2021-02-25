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
			runCustomTest(controlArduino,dataArduino);
		}
		else
		{
			std::cout << "Invalid input try again." << std::endl;
		}
		system("pause");
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
	std::string temp = "";
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
	Sleep(100);
	temp = serialRead(controlArduino);
	temp = serialRead(dataArduino);
	getData(dataArduino);
	
	return;
}

void compressionTest(){}

void adhesionTest(){}

void creepTest(){}

void StressRelaxationTest(){}

void runCustomTest(SerialPort controlArduino, SerialPort dataArduino)
{
	bool waitForName = true;
	std::string filename = "";
	std::string temp = "";
	test customTest;
	std::cout << "Enter the name of the test you would like to run. Or enter 'q' to quit." << std::endl;
	while (waitForName) 
	{
		viewAllCustomTests();
		std::cin >> filename;
		if (filename == "q")
		{
			return;
		}
		std::cout << "\033[2J\033[1;1H";
		if (doesFileExist(filename + ".txt")) 
		{
			waitForName = false;
		}
		else 
		{
			std::cout << "Test named " << filename << "does not exist."<<std::endl;
		}
	}
	customTest = readTestFromFile(filename + ".txt");
	std::cout << "---------------------------------------------" << std::endl;
	for (int i = 0; i < customTest.amountSteps; i++) 
	{
		std::cout << "Step " << (i+1) << std::endl;

		std::cout << "Distance:     " << std::to_string(customTest.steps[i].distance) << std::endl;
		std::cout << "Velocity:     " << std::to_string(customTest.steps[i].velocity) << std::endl;
		std::cout << "Acceleration: " << std::to_string(customTest.steps[i].acceleration) << std::endl<<std::endl;
	}
	std::string perform;
	std::cout << "Please confirm the test above is the Test you wish to send." << std::endl;
	std::cout << "(q) - Return to menu." << std::endl;
	std::cout << "(p) - Perform Test."   << std::endl;
	std::cin >> perform;
	if (perform == "q") 
	{
		return;
	}
	std::cout << "Sending Test..." << std::endl;
	serialWrite(controlArduino, "c");
	serialWrite(controlArduino, std::to_string(customTest.amountSteps));
	std::cout << "\033[2J\033[1;1H";
	for (int i = 0; i < customTest.amountSteps; i++)
	{
		std::cout << "Step " << (i + 1) << " sent..." << std::endl;
		serialWrite(controlArduino, std::to_string(customTest.steps[i].distance));
		serialWrite(controlArduino, std::to_string(customTest.steps[i].velocity));
		serialWrite(controlArduino, std::to_string(customTest.steps[i].acceleration));
	}

		std::cout << "\033[2J\033[1;1H";
		std::cout << "Test sent." << std::endl;
		Sleep(100);
		temp = serialRead(controlArduino);
		temp = serialRead(dataArduino);
		getData(dataArduino);

	return;
}