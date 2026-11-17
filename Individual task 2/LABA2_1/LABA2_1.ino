#include <OneWire.h>
#include <DallasTemperature.h>

const int BTN1 = 2;          
const int BTN4 = 5;         
const int ONE_WIRE_PIN = 7;  
const int LED_RED    = 13;
const int LED_GREEN  = 12;
const int LED_YELLOW = 3;

OneWire oneWire(ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);

bool autoMode = true;                        
unsigned long lastRequest = 0;
const unsigned long MEASURE_INTERVAL = 1000; 
void allLedsOff()
{
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
}

void setup()
{
  Serial.begin(9600);
  pinMode(BTN1, INPUT);
  pinMode(BTN4, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  allLedsOff();
  sensors.begin();
  sensors.setWaitForConversion(false);
  sensors.requestTemperatures();        
  lastRequest = millis();
  Serial.println("Система готова.");
}

void loop()
{
  if (digitalRead(BTN1) == HIGH && autoMode)
  {
    autoMode = false;
    allLedsOff();
    Serial.println("Автоматичний режим: ВИКЛ");
  }
  if (digitalRead(BTN4) == HIGH && !autoMode)
  {
    autoMode = true;
    Serial.println("Автоматичний режим: ВКЛ");
  }
  if (millis() - lastRequest >= MEASURE_INTERVAL)
  {
    float t = sensors.getTempCByIndex(0);
    sensors.requestTemperatures();
    lastRequest = millis();

    if (t == DEVICE_DISCONNECTED_C)
    {
      Serial.println("Помилка: датчик не знайдено");
    }
    else
    {
      Serial.print("Температура: ");
      Serial.print(t);
      Serial.println(" °C");
      if (autoMode)
      {
        allLedsOff();
        if (t < 20.0)
          digitalWrite(LED_GREEN, HIGH);  
        else if (t <= 30.0)
          digitalWrite(LED_YELLOW, HIGH);   
        else
          digitalWrite(LED_RED, HIGH);     
      }
    }
  }
}