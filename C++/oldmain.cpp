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