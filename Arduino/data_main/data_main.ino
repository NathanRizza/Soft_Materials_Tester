// Creator: Nathan Rizza
//Created: 2/4/2021
//Data arduino is COM4
void setup() {
  pinMode(10, INPUT);//Recives signals from control arduino
  Serial.begin(9600);
}
bool changed =false;

void loop() 
{
  if(digitalRead(10)== HIGH)
  {
    Serial.print(measure());
    delay(10);
    changed=true;
  }
  
  if(digitalRead(10)== LOW && changed)
  {
    changed=false;
    Serial.print('d');
  }
}

float measure()
{
  return 69;
}
