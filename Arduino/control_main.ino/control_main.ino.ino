//Nathan Rizza
//Created: 12/10/2020
//
//Control Arduino is COM3

#include <AccelStepper.h>

//AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper(1,12,11); //Red-12 Blue-11

int maxSneed = 2500;
void setup()
{ 
   Serial.begin(9600);
   stepper.setMaxSpeed(maxSneed);
   stepper.setSpeed(maxSneed);
   
   stepper.setAcceleration(10000);
   stepper.runToNewPosition(800);
   stepper.runToNewPosition(0);
   pinMode(10, OUTPUT); //commuincation channel between control and data arduino. - 10
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
  }
  else if(testID == "c")
  {
    customTestSetup();
  }
  else if(testID =="r")
  {

  }
  else if(testID =="n")
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

void customTestSetup()
{
    String distance = "d";
    String velocity = "v";
    String acceleration = "a";
    String stringSteps = "0";
    int disInt =0;
    int velInt = 0;
    int accInt =0;
    int intSteps = 0;

    stringSteps = readData();
    intSteps=stringSteps.toInt();
    Serial.println('c');
    delay(500);
    digitalWrite(10,HIGH);
    delay(1000);
    for(int i=0; i<intSteps;i++)
    {
    Serial.println('c');
    distance = readData();
    Serial.println('c');
    velocity = readData();
    Serial.println('c');
    acceleration = readData();
    
    disInt = distance.toInt();
    velInt = velocity.toInt();
    accInt = acceleration.toInt();
    
    runStep(disInt,velInt,accInt);
    }
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
      delay(300);
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
