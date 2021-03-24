#include "testMenu.h"

void TestLibrary(SerialPort controlArduino, SerialPort dataArduino)
{
	while (true)
	{
		std::cout << "\033[2J\033[1;1H";
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
			showMaxSettings();
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
		flushArduinos(dataArduino, controlArduino);
		system("pause");
		std::cout << "\033[2J\033[1;1H";
	}
}


void tensileTest(SerialPort controlArduino, SerialPort dataArduino)
{
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
	std::string fileName = "";

		std::cout << "Tensile Test Menu:" << std::endl;

		std::cout << "Velocity of the Tester? (cm/s)" << std::endl;
		std::cin >> velocityCM;
		velPulse = cmToPulse(velocityCM);

		std::cout << "How far would you like the Tester to pull in addition to the current displacement? (cm)" << std::endl;
		std::cin >> distanceCM;
		disPulse = cmToPulse(distanceCM);

		std::cout << "Acceleration of the Tester? (cm/s^2)" << std::endl;
		std::cin >> accCM;
		accPulse = cmToPulse(accCM);

		checkAll(velPulse, disPulse, accPulse);

		disString = std::to_string(disPulse);
		velString = std::to_string(velPulse);
		accString = std::to_string(accPulse);

		std::cout << "-----------------Test to Run-----------------" << std::endl;
		std::cout << "Distance(Pulses): "<< disString << std::endl;
		std::cout << "Velocity(Pulses/sec): "<< velString << std::endl;
		std::cout << "Acceleration(Pulses/sec^2): "<< accString << std::endl;
		std::cout << "---------------------------------------------" << std::endl;

		if (abandonTest())
		{
			return;
		}
		std::cout << "\033[2J\033[1;1H";

	fileName = getValidFileName();
	std::cout << "Sending test to arduino, please wait..."<< std::endl;
	serialWrite(controlArduino, "t");
	serialWrite(controlArduino, disString);
	serialWrite(controlArduino, velString);
	serialWrite(controlArduino, accString);
	std::cout << "Test Sent!" << std::endl;
	Sleep(100);
	temp = serialRead(controlArduino);
	temp = serialRead(dataArduino);
	getData(dataArduino,fileName);
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
	std::string csvFileName = "";
	std::string perform;
	test customTest;
	std::cout << "Enter the name of the test you would like to run (without \".txt\"). Or enter 'q' to quit." << std::endl;
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

	std::cout << "Please confirm the test above is the Test you wish to send." << std::endl;
	if (abandonTest) 
	{
		return;
	}

	csvFileName = getValidFileName();

	runCustomTest(controlArduino, customTest);
	getData(dataArduino,csvFileName);
	return;
}

bool abandonTest() 
{
	std::string confirmedString = "0";
	while (confirmedString != "1" && confirmedString != "2" && confirmedString != "3")
	{
		std::cout << std::endl;
		std::cout << "(1): Perform Test" << std::endl;
		std::cout << "(0): Exit without Performing Test" << std::endl;
		std::cin >> confirmedString;
		std::cout << "\033[2J\033[1;1H";
		if (confirmedString == "1")//Run
		{
			return false;
		}

		else if (confirmedString == "0")//Quit
		{
			return true;
		}
		else
		{
			std::cout << "\033[2J\033[1;1H";
			std::cout << "Invalid input try again." << std::endl;
			system("pause");
		}
	}
}

void showMaxSettings()
{
	std::cout << std::endl;
	std::cout << "------------Tester's Max Settings------------"<< std::endl;
	std::cout << "Max Speed:		" << pulseToCM(getMaxSpeed()) << " cm/sec" << std::endl;
	std::cout << "Max Distance:		" << pulseToCM(getMaxDistance()) << " cm" << std::endl;
	std::cout << "Max Acceleration:	" << pulseToCM(getMaxAcceleration()) << " cm/sec^2" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << std::endl;
}