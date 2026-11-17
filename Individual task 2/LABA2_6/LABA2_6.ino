#include <OneWire.h>
#include <DallasTemperature.h>

OneWire ow(2);
DallasTemperature s(&ow);
float t, maxT = -127;

void setup() 
{
  Serial.begin(9600);
  pinMode(4, INPUT);   
  pinMode(5, OUTPUT);  
  s.begin();
  s.setResolution(12);  
}

void loop() 
{
  s.requestTemperatures();
  t = s.getTempCByIndex(0);
  if (t > maxT) maxT = t;
  digitalWrite(5, t >= 20);      
  if (digitalRead(3)) 
  {            
    Serial.println(maxT, 4);
  }
}