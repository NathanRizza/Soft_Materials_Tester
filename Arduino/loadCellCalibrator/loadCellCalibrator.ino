
// Creator: Nathan Rizza
//Created: 3/18/2021
//Data arduino is COM4

#include <Wire.h>
#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads1115;

int16_t zero;

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

      Serial.begin(9600);
      pinMode(10, INPUT);//Recives signals from control arduino
      ads1115.begin();
      zero = ads1115.readADC_Differential_0_1();
      Serial.println("How to calibrate:");
      Serial.println("1.) Start this program with the load cell ready to accept the known weights.");
      Serial.println("2.) Add known weights after program has started.");
      Serial.println("3.) Press any key to start calibrating the load cell.");
      Serial.println("4.) The arduino will count to 10 where it will take ten measurements.");
      Serial.println("5.) After the measurements have been taken the program will spit out the average bits measured for the known weight.");
    }

    
      void loop(void)
    {
      String data=""; 
      if (Serial.available() > 0) 
      {
        calibrate();
        data = Serial.read();
      }
    }

    void calibrate()
    {
     long sum=0;
     for(int i =0;i<10;i++)
     {
      Serial.print(i);
      sum = sum+ (ads1115.readADC_Differential_0_1()-zero); ;
      delay(1000);
     }
     Serial.println();
     Serial.print("Average bits: ");
     Serial.println(sum/10);
    }
      
