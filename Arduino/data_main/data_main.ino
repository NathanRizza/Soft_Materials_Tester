
// Creator: Nathan Rizza
//Created: 2/4/2021
//
//Data arduino is COM4

#include <Wire.h>
#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads1115;

int16_t zero =0;
int16_t results=0;
long sampleingSpeed = 20;
String serialData ="temp";

    void setup(void)
    {
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads1115.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads1115.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads1115.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  ads1115.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  //ads1115.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  //ads1115.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

      Serial.begin(256000); // Use for connection to PC
      //Serial.begin(9600); //For testing in serial monitor.
      pinMode(10, INPUT);//Recives signals from control arduino
      pinMode(9, INPUT);//Recives signals from control arduino for Creep Test Start
      pinMode(8, OUTPUT);//Send signals to control arduino for Creep Test
      ads1115.begin();
    }
     
    void loop(void)
    {
      if(digitalRead(10)== HIGH)
      {
        zero = ads1115.readADC_Differential_0_1(); 
        while(digitalRead(10)==HIGH)
        {
          measureAndPrint();
          delay(50);
        }
        Serial.print('d');
        delay(5000);
      }
      if(digitalRead(9)==HIGH)
      {
        creepTest();  
      }
      changeSampleSpeed();
    }
      
void measureAndPrint()
{
      results = ads1115.readADC_Differential_0_1();
      Serial.println(abs(results-zero));
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

void changeSampleSpeed()
{
      if(Serial.available()>0)
      {
      serialData = readData();
      sampleingSpeed = atol(serialData.c_str());
      Serial.println("r");
      delay(500);
      } 
      return;
}

void creepTest()
{
 String desiredForceString = readData();
  Serial.println('c');
 String conversionFactorString = readData();
 float desiredForce = desiredForceString.toFloat();
 float conversionFactor = conversionFactorString.toFloat();
 Serial.println('b');
 zero = ads1115.readADC_Differential_0_1(); 
 //Begin reading in the force data and set the move to high.
 while(digitalRead(9)==HIGH)
 {
    if((ads1115.readADC_Differential_0_1()*9.81*conversionFactor)< desiredForce)
    {
      digitalWrite(8,HIGH);
    }
    else
    {
     digitalWrite(8,LOW);
    }
 }
}
