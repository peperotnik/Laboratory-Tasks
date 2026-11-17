int buttonPinHigher = 2;
int buttonPinLower = 7;
int ledButton = 4;
int count = 200;
unsigned long previousMillis = 0;

void setup() 
{
  pinMode(buttonPinHigher, INPUT_PULLUP);
  pinMode(buttonPinLower, INPUT_PULLUP);
  pinMode(ledButton, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  int buttonState1 = digitalRead(buttonPinHigher);
  int buttonState2 = digitalRead(buttonPinLower);
  if (buttonState1 == LOW)
  {
    if (count < 1000)
    {
    	count = count + 100;
    }
  }
  else if (buttonState2 == LOW)
  {
    if (count > 100)
    {
    	count = count - 100;
    }
  }
  digitalWrite(ledButton, HIGH);
  delay(count);
  digitalWrite(ledButton, LOW);
  delay(count);
}
