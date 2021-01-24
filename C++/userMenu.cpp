#include "userMenu.h"

void mainMenu(SerialPort controlArduino, SerialPort dataArduino)
{
	while (true)
	{
		std::cout << "Enter the number of the action you want to take then press the ENTER Key:" << std::endl;
		std::cout << "(1): Run Test" << std::endl;
		std::cout << "(2): Make Custom Test" << std::endl;
		std::cout << "(3): Manage Custom Tests" << std::endl; //add more stuff here
		std::cout << "(4): Settigns" << std::endl;
		std::cout << "(5): Help" << std::endl;
		std::cout << "(0): End Program" << std::endl;

		std::string userInput = "9";
		std::cin >> userInput;
		std::cout << "\033[2J\033[1;1H";

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
			settings();
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
		std::cout << "\033[2J\033[1;1H"; // Clear consul
	}
}

void settings()
{
	return;
}

void help()
{
	std::cout << "---How to use this Program---" << std::endl;

	system("pause");
	return;
}

//void dataOutput(int time[], int distance[], int force[])