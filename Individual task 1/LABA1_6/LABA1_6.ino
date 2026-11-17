int buttonPinRed = 2;
int buttonPinGreen = 7;
int ledButtonGreen = 4;
int ledButtonRed = 8;
int mode = 0;


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
  if(buttonState1 == LOW)//red 
  {
  mode = 1;
  }
  else if(buttonState2 == LOW)
  {
  mode = 2;
  }
  if(mode == 2)
  {
  digitalWrite(ledButtonGreen, HIGH);
  digitalWrite(ledButtonRed, HIGH);
  delay(50);
  digitalWrite(ledButtonRed, LOW);
  delay(50);
  }
  else if(mode == 1)
  {
  digitalWrite(ledButtonRed, HIGH);
  digitalWrite(ledButtonGreen, HIGH);
  delay(50);
  digitalWrite(ledButtonGreen, LOW);
  delay(50);
  }
}
