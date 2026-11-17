int buttonPinRed = 2;
int buttonPinGreen = 7;
int ledButtonGreen = 4;
int ledButtonRed = 8;
bool ledStateGreen = false;
bool ledStateRed = false;

void setup() 
{
  pinMode(buttonPinRed, INPUT_PULLUP);
  pinMode(buttonPinGreen, INPUT_PULLUP);
  pinMode(ledButtonGreen, OUTPUT);
  pinMode(ledButtonRed, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  delay(20);
  int buttonState1 = digitalRead(buttonPinRed);
  int buttonState2 = digitalRead(buttonPinGreen);
  if (buttonState1 == LOW && buttonState2 == LOW)
  {  
      ledStateGreen = false;
      ledStateRed = false;
     digitalWrite(ledButtonGreen, LOW);
 	 digitalWrite(ledButtonRed, LOW);
    return;
  }
  else if(buttonState1 == LOW)//red 
  {
    ledStateGreen = false;
    ledStateRed = true;
  }
  else if(buttonState2 == LOW)
  {
    ledStateGreen = true;
    ledStateRed = false;
  }
  digitalWrite(ledButtonGreen, ledStateGreen);
  digitalWrite(ledButtonRed, ledStateRed);
}
