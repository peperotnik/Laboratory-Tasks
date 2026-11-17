#include <OneWire.h>
#include <DallasTemperature.h>

const int BTN1 = 4;
const int BTN2 = 5;
const int BTN3 = 6;
const int BTN4 = 7;

OneWire oneWire(2);
DallasTemperature sensors(&oneWire);
DeviceAddress addr;              

int high = 30;                  
int low = 20;                    
const int MIN_T = -55;           
const int MAX_T = 125;          

void setup() {
  Serial.begin(9600);
  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);
  pinMode(BTN3, INPUT);
  pinMode(BTN4, INPUT);
  sensors.begin();
  sensors.getAddress(addr, 0);
}

void loop() {
  if (digitalRead(BTN1) == HIGH && high < MAX_T) high++;
  if (digitalRead(BTN2) == HIGH && high > MIN_T) high--;
  if (digitalRead(BTN3) == HIGH && low < MAX_T) low++;
  if (digitalRead(BTN4) == HIGH && low > MIN_T) low--;
  sensors.setHighAlarmTemp(addr, high);
  sensors.setLowAlarmTemp(addr, low);
  sensors.requestTemperatures();
  Serial.print("Температура: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print(" | Верхня межа: ");
  Serial.print(high);
  Serial.print(" | Нижня межа: ");
  Serial.println(low);
  delay(1000);
}