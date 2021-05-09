//Nathan Rizza
#include "userMenu.h"

void mainMenu(SerialPort controlArduino, SerialPort dataArduino)
{
	while (true)
	{
		ClearScreen();
		std::cout << "Enter the number of the action you want to take then press the ENTER Key:" << std::endl;
		std::cout << "(1): Run Test" << std::endl;
		//std::cout << "(2): Make Custom Test" << std::endl;
		//std::cout << "(3): Manage Custom Tests" << std::endl; 
		std::cout << "(2): Settigns" << std::endl;
		std::cout << "(3): Help" << std::endl;
		std::cout << "(0): End Program" << std::endl;

		std::string userInput = "9";
		std::cin >> userInput;
		ClearScreen();

		if (userInput == "0")
		{
			return;
		}
		else if (userInput == "1")
		{
			TestLibrary(controlArduino,dataArduino);
		}
		else if (userInput == "NA")
		{
			MakeCustomTest();

		}
		else if (userInput == "NARN")
		{
			manageCustomTests();
		}
		else if (userInput == "2")
		{
			settings(dataArduino);
		}
		else if (userInput == "3")
		{
			help();
		}
		else
		{
			std::cout << "Invalid input please try again." << std::endl;
			system("pause");
		}
		ClearScreen();
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
		ClearScreen();

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
		ClearScreen();
	}
}

void help()
{
	std::cout << "---How to use this Program---" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Data Types:" << std::endl;
	std::cout << "Int –	 	Whole number integer, positive or negative. "<<std::endl;
	std::cout << "Float – 	Number with decimal, positive or negative. " << std::endl;
	std::cout << "String –	Letters / words, no special characters. Example of special characters (%[\]!@)" << std::endl;
	std::cout << " " << std::endl;
	std::cout << "Navigation:" << std::endl;
	std::cout << "When navigating the menus, use only Ints that corresponding command you want to run." << std::endl;
	std::cout << "Data File Placement:" << std::endl;
	std::cout << "Data files are will be placed in the same folder as the application. " << std::endl;
	std::cout << "After you’re done recording data please remove the csv file from the folder to keep it tidy." << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Making Graphs in Excel:" << std::endl;
	std::cout << "To make a graph out of the collected data in excel select only the column you would like to graph and hit insert graph. " << std::endl;
	std::cout << "Selecting the time column will not produce a correctly formatted graph. " << std::endl;
	std::cout << "----------------------------" << std::endl;
	system("pause");
	return;
}