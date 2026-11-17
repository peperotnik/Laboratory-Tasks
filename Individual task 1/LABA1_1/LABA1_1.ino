int buttonPin = 2;
int count = 0;
int lastButtonState = HIGH;

void setup() 
{
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() 
{
  int buttonState = digitalRead(buttonPin);

if (buttonState == LOW && lastButtonState == HIGH)
{ 
  count ++;
  Serial.println(count);	
}
  lastButtonState = buttonState; 
  delay(100);
}
