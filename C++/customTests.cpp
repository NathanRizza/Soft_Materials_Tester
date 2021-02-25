#include "customTests.h"

namespace fs = std::filesystem;

void MakeCustomTest()
{
	test madeTest;
	bool whileMakeCont = true;
	madeTest.amountSteps = 0;
	bool confirmed = true;

	std::cout << "What would you like to name this test?" << std::endl;
	std::cin >> madeTest.name;

	while (doesFileExist(madeTest.name))
	{
		std::cout << "A Test Named " << madeTest.name << " alreadyExists, try another name." << std::endl;
		std::cin >> madeTest.name;
	}

	do
	{
		std::string makeCont = "temp";
		while (confirmed)
		{

			std::cout << "Step " << (madeTest.amountSteps + 1) << ":" << std::endl;
			std::cout << "Enter the Distance (Pulses)" << std::endl;
			std::cin >> madeTest.steps[madeTest.amountSteps].distance;
			std::cout << "Enter the Velocity (Pulses/sec)" << std::endl;
			std::cin >> madeTest.steps[madeTest.amountSteps].velocity;
			std::cout << "Enter the Acceleration (Pulses/sec)" << std::endl;
			std::cin >> madeTest.steps[madeTest.amountSteps].acceleration;

			std::string confirmedString = "temp";
			while (confirmedString != "y" && confirmedString != "n")
			{
				std::cout << "Confirm this step? (y/n)" << std::endl;
				std::cin >> confirmedString;

				if (confirmedString == "y")
				{
					confirmed = false;

				}

				if (confirmedString != "y" && confirmedString != "n")
				{
					std::cout << "Invalid input try again." << std::endl;
					system("pause");
				}

			}
			std::cout << "\033[2J\033[1;1H";
		}
		madeTest.amountSteps++;
		confirmed = true;

		makeCont = "temp";
		while (makeCont != "y" && makeCont != "n")
		{
			std::cout << "Would you like to add another Step? (y/n)" << std::endl;
			std::cin >> makeCont;

			if (makeCont == "n")
			{
				whileMakeCont = false;
			}

			if (makeCont != "y" && makeCont != "n")
			{
				std::cout << "Invalid input try again." << std::endl;
				system("pause");
			}
		}
		std::cout << "\033[2J\033[1;1H";
	} while (whileMakeCont);

	writeTestToFile(madeTest);
	std::cout << madeTest.name << " saved" << std::endl;
	return;
}
//-----------Should be Done------------
void manageCustomTests()
{

	while (true)
	{
		std::cout << "\033[2J\033[1;1H"; // Clear consul
		std::cout << "What would you like to do?" << std::endl;
		std::cout << "(1) View all Tests" << std::endl;
		std::cout << "(2) View specific Tests" << std::endl;
		std::cout << "(3) Delete specific Test" << std::endl;
		std::cout << "(0) Back to main Menu" << std::endl;
		//viewAllCustomTests(); maybe add this here?
		std::string userInput = "9";
		std::cin >> userInput;
		std::cout << "\033[2J\033[1;1H";
		if (userInput == "0")
		{
			return;
		}
		else if (userInput == "1")
		{
			viewAllCustomTests();
			system("pause");
		}
		else if (userInput == "2")
		{
			std::string chosenTestString = "temp";
			std::cout << "All Tests:" << std::endl;
			viewAllCustomTests();
			std::cout << "Choose a test to view:" << std::endl;
			std::cin >> chosenTestString;
			if (doesFileExist(chosenTestString + ".txt")) 
			{
				test chosenTest = readTestFromFile(chosenTestString + ".txt");
				printTestToScreen(chosenTest);
			}
			else 
			{
				std::cout << "File named: " << chosenTestString << ".txt doesn't Exist" << std::endl;
			}
			system("pause");
		}
		else if (userInput == "3")
		{
			std::cout << "All Tests:" << std::endl;
			viewAllCustomTests();
			std::string filetoDelete = "temp.txt";
			std::cout << "What test would you like to delete?" << std::endl;
			std::cin >> filetoDelete;
			std::cout << std::endl;
			filetoDelete = (filetoDelete + ".txt");
			deleteCustomTest(filetoDelete);
		}
		std::cout << "\033[2J\033[1;1H";
	}

}

//-----------Should be Done------------
void viewAllCustomTests() 
{
	std::string entryTemp = "temp";
	for (const auto& entry : fs::directory_iterator("."))
	{
		entryTemp = entry.path().string();

		if (entryTemp.find(".txt") != std::string::npos)
		{
			std::cout << entryTemp << std::endl;
		}
	}
}
//-----------Should be Done------------
void deleteCustomTest(std::string filename)
{
	if (doesFileExist(filename))
	{
		remove(filename.c_str()); // possible problem here but i turned the string into a c string
		std::cout << filename << " succesfully removed" << std::endl;
		system("pause");


	}
	else
	{
		std::cout << filename << " doesn't exist" << std::endl;
		system("pause");
	}
}

//Returns true if File opened Correctly
//Probably dont need since you will need to open and use a file and this only opens and closes them
bool canOpenFile(std::string filename)
{
	std::ifstream inFile;
	inFile.open(filename);

	if (inFile.fail())
	{
		inFile.close();
		std::cout << filename << " failed to open." << std::endl;
		system("pause");
		return false;
	}
	else
	{
		inFile.close();
		return true;
	}
}

//Used to see if the file already exists before making a new file with that name
//Returns true if File exists already
//-----------Should be Done------------
bool doesFileExist(std::string fullFileName)
{
	std::ifstream inFile;
	inFile.open(fullFileName);

	if (inFile.is_open())
	{
		inFile.close();
		return true;
	}
	else
	{
		inFile.close();
		return false;
	}
}


//-----------Should be Done------------
void writeTestToFile(test printTest)
{

	std::ofstream outfile(printTest.name + ".txt");
	outfile << printTest.name << '\n';
	outfile << printTest.amountSteps << '\n';
	for (int i = 0; i < printTest.amountSteps; i++)
	{
		outfile << printTest.steps[i].distance << '\n';
		outfile << printTest.steps[i].velocity << '\n';
		outfile << printTest.steps[i].acceleration << '\n';
	}
	outfile.close();
	std::cout << "Test: " + printTest.name + " saved successfully" << std::endl;
	system("pause");
	return;
}

//-----------Should be Done------------
test readTestFromFile(std::string fullFilename)
{
	test returnedTest;
	std::ifstream inFile;

	inFile.open(fullFilename);

	inFile >> returnedTest.name;
	inFile >> returnedTest.amountSteps;
	for (int i = 0; i < returnedTest.amountSteps; i++)
	{
		inFile >> returnedTest.steps[i].distance;
		inFile >> returnedTest.steps[i].velocity;
		inFile >> returnedTest.steps[i].acceleration;
	}
	inFile.close();
	return returnedTest;
}

//probably not used
std::string printTestStep(testStep i)
{
	std::string testStepString;
	testStepString = i.distance + '\n' << i.velocity + '\ n' + i.acceleration;
	return testStepString;
}

//-----------Should be Done------------
void printTestToScreen(test printTest)
{
	std::cout << "Test Name: " + printTest.name << std::endl;
	std::cout << "Number of Steps: " << printTest.amountSteps << std::endl;
	for (int i = 0; i < printTest.amountSteps; i++)
	{
		std::cout << "Step " << (i + 1) << ": (Disatance:" << printTest.steps[i].distance << ", Velocity:" << printTest.steps[i].velocity << ", Acceleration:" << printTest.steps[i].acceleration << ")" << '\n';
	}
}