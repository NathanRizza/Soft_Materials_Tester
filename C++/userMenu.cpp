#include "userMenu.h"

void mainMenu(SerialPort controlArduino, SerialPort dataArduino)
{
	while (true)
	{
		clearScreen();
		std::cout << "Enter the number of the action you want to take then press the ENTER Key:" << std::endl;
		std::cout << "(1): Run Test" << std::endl;
		std::cout << "(2): Make Custom Test" << std::endl;
		std::cout << "(3): Manage Custom Tests" << std::endl; //add more stuff here
		std::cout << "(4): Settigns" << std::endl;
		std::cout << "(5): Help" << std::endl;
		std::cout << "(0): End Program" << std::endl;

		std::string userInput = "9";
		std::cin >> userInput;
		clearScreen();

		if (userInput == "0")
		{
			return;
		}
		else if (userInput == "1")
		{
			TestLibrary(controlArduino,dataArduino);
		}
		else if (userInput == "2")
		{
			MakeCustomTest();

		}
		else if (userInput == "3")
		{
			manageCustomTests();
		}
		else if (userInput == "4")
		{
			settings(dataArduino);
		}
		else if (userInput == "5")
		{
			help();
		}
		else
		{
			std::cout << "Invalid input please try again." << std::endl;
			system("pause");
		}
		clearScreen();
	}
}

void settings(SerialPort dataArduino)
{
	while (true)
	{
		std::cout << "Enter the number of the action you want to take then press the ENTER Key:" << std::endl;
		std::cout << "(1): Change Max Speed" << std::endl;
		std::cout << "(2): Change Max Distance" << std::endl;
		std::cout << "(3): Change Max Acceleration" << std::endl;
		std::cout << "(4): Change Sampling Rate" << std::endl;
		std::cout << "(5): Change Conversion Factor" << std::endl;
		std::cout << "(6): Return to Default Settings" << std::endl;
		std::cout << "(7): Show Current Settings" << std::endl;
		std::cout << "(0): Back to Main Menu" << std::endl;

		std::string userInput = "9";
		std::cin >> userInput;
		clearScreen();

		if (userInput == "0")
		{
			return;
		}
		else if (userInput == "1")
		{
			setMaxSpeed();
		}
		else if (userInput == "2")
		{
			setMaxDistance();

		}
		else if (userInput == "3")
		{
			setMaxAcceleration();
		}
		else if (userInput == "4")
		{
			setSamplesPerSecond(dataArduino);
		}
		else if (userInput == "5")
		{
			setConversionFactor();
		}
		else if (userInput == "6")
		{
			setdefaultSettings(dataArduino);
		}
		else if (userInput == "7")
		{
			showSettings();
			system("pause");
		}
		else
		{
			std::cout << "Invalid input please try again." << std::endl;
			system("pause");
		}
		if (userInput != "7")
		{
			writeSettingsToFile();
		}
		clearScreen();
	}
}

void help()
{
	std::cout << "---How to use this Program---" << std::endl;

	system("pause");
	return;
}

void clearScreen() 
{
	std::cout << "\033[2J\033[1;1H";
}