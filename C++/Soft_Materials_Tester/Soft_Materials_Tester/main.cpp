/* Zain Ul Mustafa 2017 */

//Rules:
/*
1. Check if connection with Arduino is made
2. If Arduino is connected then take input from user in a String
3. Make a char array of the size of string + 1
4. Copy the whole string into the char array
5. Add escape sequence \n because this represents the end of a line in Serial Comm port
6. Write the whole char array into the buffer (a buffer takes the info forward to the Serial Comm Port)
7. Read from the Arduino if data is received successfully or if the action is taken as per needed
*/

//Connect with me:
/*	Twitter: http://www.twitter.com/ZainsOfficial/
	Facebook: http://www.facebook.com/ZainsOfficial/
	Github: http://github.com/ZainUlMustafa/
*/

/* This software is allowed for any user to copy, modify, merge, and distribute in any of his/her project.
Complete repository for this project is available on github. If you find this project anywhere except github, it
is to be noted that it is not made by me and not distributed by me. 
Please follow this link to get to the original repository of github for this project
Github shortened link (no spam and no ads): http://bit.ly/2vGkinQ
*/

/* PC 2 Arduino */

#include<iostream>
using namespace std;
#include<string>
#include<stdlib.h>
#include"SerialPort.h"
#include"a2pc.h"

char commport1[] = "\\\\.\\COM4"; //Arduino1 drives the motors.
char* port1 = commport1;

int main()
{
	SerialPort arduino1(port1); 
	Sleep(1000);
	if (arduino1.isConnected()) 
	{
		cout << "Connection made" << endl << endl;
	}
	else 
	{
		cout << "Error in port name" << endl << endl;
	}
		while (arduino1.isConnected()) 
		{
			cout << "Enter your command: " << endl;
			string data;
			cin >> data;
			
			serialWrite(arduino1,data);
		}
		return 0;
}