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
   //Serial.begin(9600);
   stepper.setMaxSpeed(maxSneed);
   stepper.setSpeed(maxSneed);
   
   stepper.setAcceleration(10000);
   stepper.runToNewPosition(-100);
   stepper.runToNewPosition(0);
   pinMode(10, OUTPUT); //Sends signals to data arduino to start force data collection
   pinMode(9, OUTPUT); // Sends signals data arduino to start creep test
   pinMode(7, INPUT_PULLUP); // Receives single to move up from the movement switch.
   pinMode(6, INPUT_PULLUP); // Receives single to move down from the movement switch.
   pinMode(5,OUTPUT); // Power for switch
   pinMode(3,OUTPUT); // Low mode for switch
   pinMode(2,OUTPUT); // Low mode for switch
   digitalWrite(5, HIGH);
   digitalWrite(3, LOW);
   digitalWrite(2, LOW);
}

void loop()
{ 
  
  if(Serial.available())
  {  
    menu();
  }
  if(digitalRead(7)==HIGH)
  {
    moveUp();
    stepper.setCurrentPosition(0);
  }
  if(digitalRead(6)==HIGH)
  {
    moveDown();
    stepper.setCurrentPosition(0);
  }
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
  else if(testID =="p")//creep Test
  {
    creepTestSetup();
  }
  else if(testID =="r")//Stress Relaxation Test
  {
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
    String testTimeString = readData(); //in mins
    long testTime =atol(testTimeString.c_str());
    digitalWrite(9,HIGH);
    delay(100);
    //Serial.println('b');
    delay(1000);
    creepTest(testTime);
    digitalWrite(9,LOW);
    delay(500);
    Serial.print("d");
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

void tesnsileTest(long disLong,long velLong,long accLong)
{
    runStep(disLong,velLong,accLong);
    return;  
}

void creepTest(long testTime)
{
  long currentDistance = 0;
  long maxCreepDis = 100000;
  long startTime = millis();
  long curTime = millis()-startTime;
  long testTimeMil = testTime *60*1000;
  while((curTime < testTimeMil) && (currentDistance < maxCreepDis))
  {
      if(digitalRead(8)==HIGH)
      {
          while(digitalRead(8)==HIGH)
          { 
            stepper.moveTo(currentDistance+1);
            if(stepper.run())
            {
            currentDistance = currentDistance + 1;
            }
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

void moveDown()
{
  int i = 1;
while(digitalRead(6)==HIGH)
{
  i++;
  stepper.move(i);
  stepper.run();
}

}

void moveUp()
{

int i = -1;
while(digitalRead(7)==HIGH)
{
  i--;
  stepper.move(i);
  stepper.run();
}
return;
}



//End of File
