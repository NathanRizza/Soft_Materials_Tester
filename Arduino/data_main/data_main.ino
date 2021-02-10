
// Creator: Nathan Rizza
//Created: 2/4/2021
//Data arduino is COM4

        #include <Wire.h>
    #include <Adafruit_ADS1015.h>
     
    Adafruit_ADS1015 ads1115;
     
    void setup(void)
    {
      Serial.begin(9600);
      //Serial.println("Hello!");
      pinMode(10, INPUT);//Recives signals from control arduino
      //Serial.println("Getting single-ended readings from AIN0..3");
      //Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV)");
      ads1115.begin();
    }
     
    void loop(void)
    {
      measureAndPrint();
      delay(1000);
      if(digitalRead(10)== HIGH)
      {
        while(digitalRead(10)==HIGH)
        {
          measureAndPrint();
          delay(1000);
        }
        Serial.print('d');
        delay(5000);
      }
    }
      
void measureAndPrint()
{
      
    int16_t adc0, adc1;
    //adc2, adc3;
    adc0 = ads1115.readADC_SingleEnded(0);
    //adc1 = ads1115.readADC_SingleEnded(1);
    //adc2 = ads1115.readADC_SingleEnded(2);
    //adc3 = ads1115.readADC_SingleEnded(3);
    Serial.println(adc0);
    //Serial.println(adc1);
    //Serial.println(adc2);
    //Serial.println(adc3);
}
