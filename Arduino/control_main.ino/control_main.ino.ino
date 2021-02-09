//Nathan Rizza
//Created: 12/10/2020
//
//

#include <AccelStepper.h>

//AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper(1,12,11); //Red-12 Blue-11

int maxSneed = 2500;
void setup()
{ 
   Serial.begin(9600);
   stepper.setMaxSpeed(maxSneed);
   //stepper.moveTo(800);
   stepper.setSpeed(maxSneed);
   //stepper.runSpeedToPosition();
   //stepper.moveTo(0);
   //stepper.setSpeed(2500);
   //stepper.runSpeedToPosition();
   
   stepper.setAcceleration(10000);
   stepper.runToNewPosition(800);
   stepper.runToNewPosition(0);
   pinMode(10, OUTPUT); //commuincation channel between control and data arduino.
}

void loop()
{ 
    menu();
}

void menu(void)
{
  String testID = "p";
  testID = readData();
  testMenu(testID);
  return;
}  

void testMenu(String testID)
{
  if(testID == "t")
  {
    tensileSetup();
    //Serial.println("Test Completed Sucsessfully");
  }
  else if(testID == "e")
  {
    while(true)
    {
    Serial.print("echo");
    String data = readData();
    Serial.print(100);
    }
  }
  else if(testID =="r")
  {
    int i=0;
    stepper.moveTo(1600);//http://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html#ace236ede35f87c63d18da25810ec9736
    while(i <1600)
    {
      if(stepper.run())
      {
      i++;
      }
    }
  }
  else if(testID =="n")
  {
    stepper.runToNewPosition(10000);
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

    Serial.println('b');
    delay(500);
    digitalWrite(10,HIGH);
    delay(1000);
    tesnsileTest(disInt,velInt,accInt);
    digitalWrite(10,LOW);
    delay(500);
    Serial.println("d");
    
    delay(5000);
    stepper.setSpeed(maxSneed);
    stepper.setAcceleration(0);
    stepper.runToNewPosition(0);
    
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
    runStep(disInt,velInt,accInt);
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
