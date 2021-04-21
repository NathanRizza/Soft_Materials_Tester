//Nathan Rizza
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
			std::cout << "Tensile Test Menu:" << std::endl;
			tensileTest(controlArduino, dataArduino);
		}
		else if (userInput == "2")
		{
			showMaxSettings();
			std::cout << "Compression Test Menu:" << std::endl;
			tensileTest(controlArduino, dataArduino);
		}
		else if (userInput == "3")
		{
			showMaxSettings();
			std::cout << "Adhesion Test Menu:" << std::endl;
			tensileTest(controlArduino, dataArduino);
		}
		else if (userInput == "4")
		{
			std::cout << "Creep Test Menu:" << std::endl;
			creepTest(controlArduino, dataArduino);
		}
		else if (userInput == "5")
		{
			std::cout << "Stress Relaxation Test Menu:" << std::endl;
			StressRelaxationTest();
		}
		else if (userInput == "6")
		{
			std::cout << "Custom Test Menu:" << std::endl;
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

		std::cout << "Displacement of Tester? (cm) (\"+\"= Up,\"-\"=Down)" << std::endl;
		std::cin >> distanceCM;
		disPulse = cmToPulse(distanceCM);


		std::cout << "Velocity of the Tester? (cm/s)" << std::endl;
		std::cin >> velocityCM;
		velPulse = cmToPulse(velocityCM);

		std::cout << "Acceleration of the Tester? (cm/s^2)" << std::endl;
		std::cin >> accCM;
		accPulse = cmToPulse(accCM);
		
		if (velPulse < 0)
		{
			velPulse = velPulse * -1;
		}
		if (accPulse < 0)
		{
			accPulse = accPulse * -1;
		}

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
	getData(dataArduino, fileName, velPulse, accPulse);
	return;
}

void compressionTest(){}

void adhesionTest(){}

void creepTest(SerialPort controlArduino, SerialPort dataArduino)
{
	float forceN = 0;
	int testTimeInt = 0;
	std::string forceString = "d";
	std::string testTime = "0";
	std::string temp = "";
	std::string fileName = "";

	std::cout << "Enter the constent force you would like exerted onto the sample in Newtons. (float)" << std::endl;
	std::cin >> forceN;
	
	while (forceN > 95) 
	{
		std::cout << "\033[2J\033[1;1H";
		std::cout << "Max force cannot be greater than 95N, please enter a smaller value." << std::endl;
		std::cin >> forceN;
	}

	std::cout << "Enter the time you would like the sample to undergo the constant force in minutes. (int)" << std::endl;
	std::cin >> testTimeInt;
	testTime = std::to_string(testTimeInt);

	forceString = std::to_string(forceN);

	if (abandonTest())
	{
		return;
	}
	std::cout << "\033[2J\033[1;1H";

	fileName = getValidFileName();
	std::cout << "Sending test to arduino, please wait..." << std::endl;
	serialWrite(controlArduino, "r");
	serialWrite(controlArduino, testTime);
	serialWrite(dataArduino, forceString); //In this experiment Data is collected from the control arduino
	serialWrite(dataArduino, std::to_string(getConversionFactor()));
	std::cout << "Test Sent!" << std::endl; 
	Sleep(100);
	temp = serialRead(controlArduino);
	temp = serialRead(dataArduino);
	getCreepTestData(controlArduino,fileName);
	return;

}

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
	getDataNoDistance(dataArduino,csvFileName);

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
	std::cout << "Max Distance:		" << pulseToCM(getMaxDistance()) << " cm" << std::endl;
	std::cout << "Max Speed:		" << pulseToCM(getMaxSpeed()) << " cm/sec" << std::endl;
	std::cout << "Max Acceleration:	" << pulseToCM(getMaxAcceleration()) << " cm/sec^2" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << std::endl;
}