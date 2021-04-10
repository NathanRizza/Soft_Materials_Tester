//Nathan Rizza
//Created: 12/10/2020
//
//Control Arduino is COM3

#include <AccelStepper.h>

//AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

int CW = 11; //Green 
int CP = 12; //Yellow
AccelStepper stepper(1,CP,CW); // 1 if for direction.
int maxSneed = 2500;

void setup()
{ 
   Serial.begin(256000);
   stepper.setMaxSpeed(maxSneed);
   stepper.setSpeed(maxSneed);
   
   stepper.setAcceleration(10000);
   stepper.runToNewPosition(-100);
   stepper.runToNewPosition(0);
   pinMode(10, OUTPUT); //Sends signals to data arduino to start force data collection
   pinMode(9, OUTPUT); // Sends signals data arduino to start creep test
   pinMode(8, INPUT); // Recives signals from data arduino to keep creep test on track
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
  if(testID == "t") //Tensile/Compression/AdhesionTest
  {
    tensileSetup();
  }
  else if(testID == "c")//Custom Test
  {
    customTestSetup();
  }
  else if(testID =="r")//Screep Test
  {
    creepTestSetup();
  }
  else if(testID =="n")
  {

  }
  returnToHome();
  return;
}


void tensileSetup()
{
    String distance = "d";
    String velocity = "v";
    String acceleration = "a";
    long disLong =0;
    long velLong = 0;
    long accLong =0;
    
    Serial.println('c');
    distance = readData();
    Serial.println('c');
    velocity = readData();
    Serial.println('c');
    acceleration = readData();
    
    //convert Strings to ints
        
    disLong = atol(distance.c_str());
    velLong = atol(velocity.c_str());
    accLong = atol(acceleration.c_str());
    
    Serial.println('b');
    delay(500);
    digitalWrite(10,HIGH);
    delay(1000);
    tesnsileTest(disLong,velLong,accLong);
    digitalWrite(10,LOW);
    delay(500);
    Serial.println("d");
    
    return;
}

void customTestSetup()
{
    String distance = "d";
    String velocity = "v";
    String acceleration = "a";
    String stringSteps = "0";
    long disLong =0;
    long velLong = 0;
    long accLong =0;
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
    
    disLong = atol(distance.c_str());
    velLong = atol(velocity.c_str());
    accLong = atol(acceleration.c_str());
    
    runStep(disLong,velLong,accLong);
    }
    digitalWrite(10,LOW);
    delay(500);
    Serial.println("d");
         
    return;
}

void creepTestSetup()
{
    Serial.println('c');
    long testTime = readData(); //in mins
    digitalWrite(9,HIGH);
    delay(100);
    Serial.println('b');
    delay(1000);
    creepTest(testTime);
    digitalWrite(9,LOW);
    delay(500);
    Serial.println("d");
    return;
}


void runStep(long distance, long velocity, long acceleration)
{
  if(velocity>maxSneed)
  {
  stepper.setMaxSpeed(maxSneed);
  }
  else
  {
  stepper.setMaxSpeed(velocity);  
  }
  stepper.setAcceleration(acceleration);
  
  stepper.runToNewPosition(-distance);
     
  return;
}

void tesnsileTest(long disInt,long velInt,long accInt)
{
    runStep(disInt,velInt,accInt);
    return;  
}

void creepTest(int testTime, int maxDistance)
{
  int currentDistance = 0;
  while()//TIME < TestTime && Position < max distance
  {
      if(digitalRead(8)==HIGH)
      {
          while(digitalRead(8)==HIGH)
          { 
            stepper.moveTo(currentDistance+1);
            stepper.run();
            currentDistance = currentDistance + 1;
          }
          Serial.println(currentDistance);//Print Position
      }
  }
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

void returnToHome()
{
    delay(5000);
    stepper.setMaxSpeed(maxSneed);
    stepper.setAcceleration(0);
    stepper.runToNewPosition(0);
}

bool isPositive(long distance)
{
if(distance > 0)
{
return true;
}
else
{
return false;
}
}
