#include <OneWire.h>
#include <DallasTemperature.h>


const int PINTEMP = 2;
const int PINBTN1 = 3;
const int PINBTN2 = 4;
const int PINLED = 5;
const float TMIN = 10.0;
const float TMAX = 36.0;


OneWire oneWire(PINTEMP);
DallasTemperature sensors(&oneWire);
bool ledEnabled = true;


void setup() {
  Serial.begin(9600);
  pinMode(PINBTN1, INPUT);
  pinMode(PINBTN2, INPUT);
  pinMode(PINLED, OUTPUT);
  sensors.begin();
}


void loop() {
  if(digitalRead(PINBTN1) == HIGH)
  {
    ledEnabled = false;
  }
  if(digitalRead(PINBTN2) == HIGH)
  {
    ledEnabled = true;
  }
  sensors.requestTemperatures();
  float t = sensors.getTempCByIndex(0);
  int brightness = 0;
  if(ledEnabled && t != DEVICE_DISCONNECTED_C)
  {
    float tc = constrain(t, TMIN, TMAX);
    brightness = map((long)(tc * 10), (long)(TMIN * 10), (long)(TMAX * 10), 0 , 255);
    brightness = constrain(brightness, 0 , 255);
  }
  analogWrite(PINLED, brightness);
  Serial.print("T = ");
  Serial.print(t);
  Serial.print("C, BRIGHTNESS = ");
  Serial.print(", FUNCTION ");
  Serial.print(ledEnabled ? "ON" : "OFF");
  delay(100);


}
