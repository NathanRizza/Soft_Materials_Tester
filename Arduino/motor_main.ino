// ConstantSpeed.pde
// -*- mode: C++ -*-
//
// Shows how to run AccelStepper in the simplest,
// fixed speed mode with no accelerations
/// \author  Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2009 Mike McCauley
// $Id: ConstantSpeed.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

//AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper(1,12,11);

void setup()
{  
   Serial.begin(9600); // COM27
   stepper.setMaxSpeed(1000);
   stepper.setSpeed(1000);
   stepper.setAcceleration(10000.0);
   pinMode(13, OUTPUT); //Connection Between Movement Arduino and Data Collection Arduino
   stepper.runToNewPosition(800);
   stepper.runToNewPosition(0);
   Serial.println("ready");
}

void loop()
{ 
  
    menu();
}

void menu(void)
{
  String testID = "p";
  testID = readData();
  if(testID.equals("t"))
  {
    tensileSetup();
  }
  return;
}  

void testMenu(String testID)
{
  if(testID == "t")
  {
  tensileSetup();
  //Serial.println("Test Completed Sucsessfully");
  }
  if(testID == "")
  {
    
  }
  if(testID == "")
  {
  
  }
  return;
}


void tensileSetup()
{
    String distance = "d";
    String velocity = "v";
    String acceleration = "a";
    int disInt =0;
    int velInt = 0;
    int accInt =0;
    
    Serial.println('c');
    distance = readData();
    Serial.println('c');
    velocity = readData();
    Serial.println('c');
    acceleration = readData();
    
    //convert Strings to ints
    
    disInt = distance.toInt();
    velInt = velocity.toInt();
    accInt = acceleration.toInt();

   // Serial.println("d");
    
    //Perform test and Indicate that Data Needs to be collected
    tesnsileTest(disInt,velInt,accInt);

    //Serial.println("end");
    
    return;
}

void runStep(int distance, int velocity, int acceleration)
{
  stepper.setSpeed(velocity);
  stepper.setAcceleration(acceleration);
  stepper.runToNewPosition(distance);
  return;
}

void tesnsileTest(int disInt,int velInt,int accInt)
{
    runStep(disInt,velInt,accInt); //move up
    delay(5000);

    stepper.setSpeed(1000);
    stepper.setAcceleration(0);
    stepper.runToNewPosition(-disInt);

    Serial.println("d");
    return;  
}

String readData()
{
  String info;
  while(true)
  {
  if(Serial.available()>0)
     {
      delay(500);
      info = Serial.readStringUntil('\n');
      flushRead();
      return info;
     }
  }
      
}

void flushRead()
{
  char temp;
  while(Serial.available()>0)
  {
    temp = Serial.read();
  }
  return;
}
