int buttonPin = 4;
int count = 0;
int lastButtonState = HIGH;
int ledButton = 3;
const unsigned long doubleClickTime = 400;
unsigned long lastPressTime = 0;
bool ledState = false;

void setup() 
{
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledButton, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  int buttonState = digitalRead(buttonPin);
  if (millis() - lastPressTime > doubleClickTime && count == 1)
  {
    count = 0;
  }

if (buttonState == LOW && lastButtonState == HIGH)
{ 
  count ++;
  if (count == 1)
  {
    lastPressTime = millis();
  }
  else if (count == 2)
  {
    if (millis() - lastPressTime < doubleClickTime)
    {
      ledState = !ledState;
      digitalWrite(ledButton, ledState);
      count = 0;
    }
  }
      
}
  lastButtonState = buttonState;
}
