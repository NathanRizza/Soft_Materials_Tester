#include<iostream>
#include<string>
#include<ctime>
#include <filesystem>
#include <fstream>  
#include<cstdlib>
#include <stdio.h>
#include"SerialPort.h"
#include"testStep.h"
#include"test.h"

using namespace std;
namespace fs = std::filesystem;

void mainMenu();
void settings();
void help();
//string sendCommand(SerialPort arduino, string command);
void dataOutput(int time[], int distance[], int force[]);
void sendTest();
void runCustomTest();
void MakeCustomTest();
void manageCustomTests();
void viewAllCustomTests();
void deleteCustomTest(string filename);
bool canOpenFile(string filename);
bool doesFileExist(string fullFileName);
void writeTestToFile(test printTest);
string printTestStep(testStep i);
void printTestToScreen(test printTest);
test readTestFromFile(string filename);

void TestLibrary();
void tensileTest();
void compressionTest();
void adhesionTest();
void creepTest();
void StressRelaxationTest();
void waitTillRecived(SerialPort arduino);
void sendCommand(SerialPort arduino, string data);

char output[MAX_DATA_LENGTH];
char commport1[] = "\\\\.\\COM4";
char commport2[] = "\\\\.\\COM3";
char* port1 = commport1;
char* port2 = commport2;
char incomming[MAX_DATA_LENGTH];
bool studentMode = 1;
bool mainCont =true;

SerialPort arduino1(port1); // For Movement
//SerialPort arduino2(port2); // For Data

int main() 
{
	sendCommand(arduino1,"meme");

	//if (arduino1.isConnected()) 
	if(true) //Pretend that we have a connection
	{
		cout << "Connection is Established" << endl;

		while (mainCont) 
		{
			mainMenu();
		}
	}
	else 
	{
		cout << "Error connecting to the arduino" << endl;

	}

	//Cont at 13 when he pulls up the arduino ide

	return 0;
}

void mainMenu()
{
	cout << "Enter the number of the action you want to take then press the ENTER Key:" << endl;
	cout << "(1): Run Test" << endl;
	cout << "(2): Make Custom Test" << endl;
	cout << "(3): Manage Custom Tests" << endl; //add more stuff here
	cout << "(4): Settigns" << endl;
	cout << "(5): Help" << endl;
	cout << "(0): End Program" << endl;

	string userInput = "9";
	cin >> userInput;

	if (userInput == "0")
	{
		mainCont = false;
		return;
	}
	else if (userInput == "1") 
	{
		TestLibrary();
	}
	else if (userInput == "2") 
	{
		cout << "\033[2J\033[1;1H";
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
	cout << "Invalid input please try again." << endl;
	system("pause");
	}
	cout << "\033[2J\033[1;1H"; // Clear consul
}

void settings() 
{
	return;
}

void help() 
{
		cout << "---How to use this Program---" << endl;

		system("pause");
		return;
}

void dataOutput(int time[], int distance[], int force[]) 
{

}

//add a type of test variable to the send test
void sendTest() 
{

} 

//-----------Should be Done------------
void MakeCustomTest() 
{
	test madeTest;
	bool whileMakeCont = true;
	madeTest.amountSteps = 0;
	bool confirmed = true;
	
	cout << "What would you like to name this test?" << endl;
	cin >> madeTest.name;

	while (doesFileExist(madeTest.name))
	{
		cout << "A Test Named " << madeTest.name << " alreadyExists, try another name." << endl;
		cin >> madeTest.name;
	}
	
	do 
	{
		string makeCont = "temp";
		while (confirmed)
		{

			cout << "Step " << (madeTest.amountSteps+1) << ":" << endl;
			cout << "Enter the Distance (Pulses)" << endl;
			cin >> madeTest.steps[madeTest.amountSteps].distance;
			cout << "Enter the Velocity (Pulses/sec)" << endl;
			cin >> madeTest.steps[madeTest.amountSteps].velocity;
			cout << "Enter the Acceleration (Pulses/sec)" << endl;
			cin >> madeTest.steps[madeTest.amountSteps].acceleration;

			string confirmedString = "temp";
			while (confirmedString != "y" && confirmedString != "n")
			{
				cout << "Confirm this step? (y/n)" << endl;
				cin >> confirmedString;

				if (confirmedString == "y")
				{
					confirmed = false;

				}

				if (confirmedString != "y" && confirmedString != "n")
				{
					cout << "Invalid input try again." << endl;
					system("pause");
				}

			}
			cout << "\033[2J\033[1;1H";
		}
		madeTest.amountSteps++;
		confirmed = true;

		makeCont = "temp";
		while (makeCont != "y" && makeCont != "n")
		{
			cout << "Would you like to add another Step? (y/n)" << endl;
			cin >> makeCont;

			if (makeCont == "n")
			{
				whileMakeCont = false;
			}

			if (makeCont != "y" && makeCont != "n")
			{
				cout << "Invalid input try again." << endl;
				system("pause");
			}
		}
		cout << "\033[2J\033[1;1H";
	} while (whileMakeCont);

	writeTestToFile(madeTest);
	cout << madeTest.name << " saved" << endl;
	return;
}
//-----------Should be Done------------
void manageCustomTests() 
{
	
	while (true)
	{
		cout << "\033[2J\033[1;1H"; // Clear consul
		cout << "What would you like to do?" << endl;
		cout << "(1) View all Tests" << endl;
		cout << "(2) View specific Tests" << endl;
		cout << "(3) Delete specific Test" << endl;
		cout << "(0) Back to main Menu" << endl;
		//viewAllCustomTests(); maybe add this here?
		string userInput = "9";
		cin >> userInput;
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
			string chosenTestString = "temp";
			cout << "All Tests:" << endl;
			viewAllCustomTests();
			cout << "Choose a test to view:" << endl;
			cin >> chosenTestString;
			test chosenTest = readTestFromFile(chosenTestString + ".txt");
			printTestToScreen(chosenTest);
			system("pause");
		}
		else if (userInput == "3")
		{
			cout << "All Tests:" << endl;
			viewAllCustomTests();
			string filetoDelete = "temp.txt";
			cout << "What test would you like to delete?" << endl;
			cin >> filetoDelete;
			cout << endl;
			filetoDelete = (filetoDelete+".txt");
			deleteCustomTest(filetoDelete);
		}
		cout << "\033[2J\033[1;1H";
	}

}

//-----------Should be Done------------
void viewAllCustomTests() //not done we still need this to print them all out to the screen somehow
{
	string entryTemp = "temp";
	for (const auto& entry : fs::directory_iterator("."))//backslash error maybe
	{
		entryTemp = entry.path().string();
		
		if (entryTemp.find(".txt") != string::npos)
		{
			cout << entryTemp << endl;
		}
	}
}
//-----------Should be Done------------
void deleteCustomTest(string filename)
{
	if (doesFileExist(filename))
	{
		remove(filename.c_str()); // possible problem here but i turned the string into a c string
		cout << filename << " succesfully removed" << endl;
		system("pause");
		

	}
	else
	{
		cout << filename << " doesn't exist" << endl;
		system("pause");
	}
}

//Returns true if File opened Correctly
//Probably dont need since you will need to open and use a file and this only opens and closes them
bool canOpenFile(string filename)
{
	ifstream inFile;
	inFile.open(filename);
	
	if (inFile.fail())
	{
		inFile.close();
		cout << filename << " failed to open." << endl;
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
bool doesFileExist(string fullFileName) 
{
	ifstream inFile;
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

	ofstream outfile(printTest.name + ".txt");
	outfile << printTest.name << '\n';
	outfile << printTest.amountSteps <<'\n';
	for (int i = 0; i < printTest.amountSteps; i++)
	{
		outfile << printTest.steps[i].distance << '\n';
		outfile << printTest.steps[i].velocity << '\n';
		outfile << printTest.steps[i].acceleration << '\n';
	}
	outfile.close();
	cout << "Test: " + printTest.name + " saved successfully" << endl;
	system("pause");
	return;
}

//-----------Should be Done------------
test readTestFromFile(string filename)
{
	test returnedTest;
	ifstream inFile;

	inFile.open(filename);

	inFile >> returnedTest.name;
	inFile >> returnedTest.amountSteps;
	for (int i=0; i < returnedTest.amountSteps; i++)
	{
		inFile >> returnedTest.steps[i].distance;
		inFile >> returnedTest.steps[i].acceleration;
		inFile >> returnedTest.steps[i].velocity;
	}
	inFile.close();
	return returnedTest;
}

//probably not used
string printTestStep(testStep i)
{
	string testStepString;
	testStepString = i.distance + '\n' << i.velocity + '\ n' + i.acceleration;
	return testStepString;
}
//-----------Should be Done------------
void printTestToScreen(test printTest)
{
	cout << "Test Name: " + printTest.name << endl;
	cout << "Number of Steps: " << printTest.amountSteps << endl;
	for (int i = 0; i < printTest.amountSteps; i++)
	{
		cout << "Step " << (i+1) << ": (Disatance:" << printTest.steps[i].distance << ", Velocity:" << printTest.steps[i].velocity << ", Acceleration:" << printTest.steps[i].acceleration << ")" << '\n';
	}
}

//---------------Regular Tests Below-------------

void TestLibrary()
{
	while (true)
	{
		cout << "\033[2J\033[1;1H"; // Clear consul
		cout << "What test would you like to run?" << endl;
		cout << "(1): Tensile Test" << endl;
		cout << "(2): Compression Test" << endl;
		cout << "(3): Adhesion Test" << endl;
		cout << "(4): Creep Test" << endl;
		cout << "(5): Stress Relaxation Test" << endl;
		cout << "(6): Run Custom Test" << endl;
		cout << "(0): Back to Main Menu" << endl;

		string userInput = "9";
		cin >> userInput;
		if (userInput == "0")
		{
			return;
		}
		else if (userInput == "1")
		{
			tensileTest();
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
			cout << "Invalid input try again." << endl;
			system("pause");
		}
		cout << "\033[2J\033[1;1H";
	}
}


void tensileTest() 
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
	string disString = "d";
	string velString = "v";
	string accString = "a";
	while (done)
	{

		cout << "Enter the Length of the Material in (mm)" << endl;
		cin >> matLength;
		cout << "Enter the Width of the Material in (mm)" << endl;
		cin >> matWidth;
		cout << "Enter the Thickness of the Material in (mm)" << endl;
		cin >> matThickness;

		cout << "How far would you like the Tester to pull in addition to the current displacement? (cm)" << endl;
		cin >> distanceCM;
		distanceCM = distanceCM * (800 / 0.3); //might have to move these equations because of truncation!
		disPulse = distanceCM;
		disString = disPulse;

		cout << "Velocity of the Tester? (cm/s)" << endl;
		cin >> velocityCM;
		velocityCM = velocityCM * (800 / 0.3);
		velString = velPulse;

		cout << "Acceleration of the Tester? (cm/s)" << endl;
		cin >> accCM;
		accCM = accCM * (800 / 0.3);
		accPulse = accCM;
		accString = accPulse;


		cout << endl;
		cout << "(1): Perform Test" << endl;
		cout << "(2): Re-enter Test" << endl;
		cout << "(3): Exit without Performing Test" << endl;

		string confirmedString = "0";
		while (confirmedString != "1" && confirmedString != "2" && confirmedString != "3")
		{
			cin >> confirmedString;

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
				cout << "Invalid input try again." << endl;
				system("pause");
			}

		}
		cout << "\033[2J\033[1;1H";
	}


	sendCommand(arduino1,"t");
	waitTillRecived(arduino1);
	sendCommand(arduino1,disString);
	waitTillRecived(arduino1);
	sendCommand(arduino1,velString);
	waitTillRecived(arduino1);
	sendCommand(arduino1,accString);
	waitTillRecived(arduino1);

	cout << "Test Completed" << endl;
	//do data later right here

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
	sendTest();
}

//sends out a command and recives a responce from the arduino
/*
string sendCommand(SerialPort arduino, string command)
{
	char* charArray = new char[command.size() + 1];
	copy(command.begin(), command.end(), charArray);
	charArray[command.size()] = '\n'; // Read in the command untill \n
	//Commands like this can be used in combination in order to create the tests.
	arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
	arduino.readSerialPort(output, MAX_DATA_LENGTH);

	cout << output;
	delete[] charArray;

	return "temp";
}
*/

//Sends a command to the arduino
void sendCommand(SerialPort arduino, string data)
{
	if (arduino.isConnected()) 
	{

		char* charArray = new char[data.size() + 1];
		copy(data.begin(), data.end(), charArray);
		charArray[data.size()] = '\n';

		arduino.writeSerialPort(charArray, MAX_DATA_LENGTH);
		//arduino.readSerialPort(output, MAX_DATA_LENGTH);

		//cout << ">> " << output << endl;

		delete[] charArray;
	}
	else 
	{
		cout << "error sending command to movement arduino" << endl;
	}
}
//waits for the arduino to send back a command
void waitTillRecived(SerialPort arduino)
{
	bool waiting = true;
	while (waiting) 
	{
		arduino.readSerialPort(output, MAX_DATA_LENGTH);

		if (output =="c") 
		{
			waiting = false;
			cout << "cont" << endl;
		}
		else if (output == "d") 
		{
			waiting = false;
			cout << "done!" << endl;
		}
	}
}