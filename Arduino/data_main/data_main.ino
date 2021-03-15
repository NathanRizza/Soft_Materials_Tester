
// Creator: Nathan Rizza
//Created: 2/4/2021
//Data arduino is COM4

#include <Wire.h>
#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads1115;

int16_t zero;
int16_t results;


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

      Serial.begin(256000);
      pinMode(10, INPUT);//Recives signals from control arduino
      ads1115.begin();
  return;
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
    }
      
void measureAndPrint()
{
      results = ads1115.readADC_Differential_0_1(); 
      Serial.println(abs(results-zero));
      return;
}
