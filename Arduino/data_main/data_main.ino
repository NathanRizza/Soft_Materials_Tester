
// Creator: Nathan Rizza
//Created: 2/4/2021
//Data arduino is COM4

    #include <Wire.h>
    #include <Adafruit_ADS1015.h>
 
    Adafruit_ADS1115 ads1115; // construct an ads1115 at address 0x49
    
void setup(void) {
  pinMode(10, INPUT);//Recives signals from control arduino
  Serial.begin(9600);
  ads1115.begin();  // Initialize ads1115
}
bool changed =false;

void loop() 
{
  measureAndPrint();
  delay(1000);
  if(digitalRead(10)== HIGH)
  {
    while(digitalRead(10)==HIGH)
    {
    //Serial.print(measure());
    measureAndPrint();
    delay(1000);
    }
   Serial.print('d');
   delay(5000);
  }
}

String measureAndPrint()
{
  int16_t adc0, adc1;
  //adc2, adc3;
  adc0 = ads1115.readADC_SingleEnded(0);
  adc1 = ads1115.readADC_SingleEnded(1);
  //adc2 = ads1115.readADC_SingleEnded(2);
  //adc3 = ads1115.readADC_SingleEnded(3);
  Serial.println(adc0);
  Serial.println(adc1);
  //Serial.println(adc2);
  //Serial.println(adc3);
  return;
}
