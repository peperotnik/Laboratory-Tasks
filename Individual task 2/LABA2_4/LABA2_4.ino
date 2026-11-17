#include <OneWire.h>
#include <DallasTemperature.h>

const int BTN1 = 2;   
const int BTN2 = 4;   
const int BTN3 = 5;   
const int BTN4 = 6;   
const int LED_RED    = 13;
const int LED_GREEN  = 12;
const int LED_YELLOW = 3;  
const int ONE_WIRE_PIN = 7;

OneWire oneWire(ONE_WIRE_PIN);
DallasTemperature sensors(&oneWire);

enum Mode { MODE_AUTO, MODE_MANUAL, MODE_ALL };
Mode mode = MODE_AUTO;

int  manualIndex = -1;    
bool allOn = false;        
bool showTemp = false;     
float temperature = 0;
unsigned long lastRequest = 0;
bool waitingConversion = false;
const unsigned long CONVERSION_TIME = 800; 
const unsigned long MEASURE_PERIOD  = 1000;
bool lastState[4] = {false, false, false, false};

bool pressed(int idx, int pin) 
{
  bool now = digitalRead(pin) == HIGH;
  bool result = now && !lastState[idx];
  lastState[idx] = now;
  return result;
}

void setLeds(bool r, bool g, bool y) 
{
  digitalWrite(LED_RED,    r);
  digitalWrite(LED_GREEN,  g);
  digitalWrite(LED_YELLOW, y);
}

void setup() {
  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);
  pinMode(BTN3, INPUT);
  pinMode(BTN4, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  setLeds(LOW, LOW, LOW);
  Serial.begin(9600);
  sensors.begin();
  sensors.setWaitForConversion(false);
  Serial.println("Сенсорне меню готове");
}

void loop() 
{
  if (pressed(0, BTN1)) 
  {            
    mode = MODE_AUTO;
    Serial.println("Режим: автоматичний");
  }

  if (pressed(1, BTN2)) 
  {
    mode = MODE_MANUAL;
    manualIndex = (manualIndex + 1) % 3;
    setLeds(manualIndex == 0, manualIndex == 1, manualIndex == 2);
    Serial.println("Режим: ручний");
  }

  if (pressed(2, BTN3)) 
  {            
    showTemp = !showTemp;
    Serial.println(showTemp ? "Вивід температури: ВКЛ" : "Вивід температури: ВИКЛ");
  }

  if (pressed(3, BTN4)) {            
    mode = MODE_ALL;
    allOn = !allOn;
    setLeds(allOn, allOn, allOn);
    Serial.println(allOn ? "Усі світлодіоди: ВКЛ" : "Усі світлодіоди: ВИКЛ");
  }

  unsigned long now = millis();
  if (!waitingConversion && now - lastRequest >= MEASURE_PERIOD)
 {
    sensors.requestTemperatures();  
    lastRequest = now;
    waitingConversion = true;
  }
  if (waitingConversion && now - lastRequest >= CONVERSION_TIME) 
  {
    float t = sensors.getTempCByIndex(0);
    waitingConversion = false;

    if (t != DEVICE_DISCONNECTED_C) 
    {
      temperature = t;
      if (showTemp) {                
        Serial.print("Температура: ");
        Serial.print(temperature);
        Serial.println(" °C");
      }
      if (mode == MODE_AUTO) 
      {
        if (temperature < 20)       setLeds(LOW, HIGH, LOW);
        else if (temperature <= 30) setLeds(LOW, LOW, HIGH);
        else                        setLeds(HIGH, LOW, LOW);
      }
    } else {
      Serial.println("Датчик не знайдено!");
    }
  }

  delay(20);
}