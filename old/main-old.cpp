int buttonState = 0;
int lastButtonState = 0;
int buttonPushCounter = 0;

void setup()
{
  pinMode(2, INPUT);
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  buttonState = digitalRead(2);
  
  if (buttonState != lastButtonState) {
    
    if (buttonState == HIGH) {
      buttonPushCounter += 1;
    delay(5); 
  }
  
  lastButtonState = buttonState;
  
  if (buttonPushCounter == 1) {
    Serial.println("1st");
  } else if (buttonPushCounter == 2){
    digitalWrite(LED_BUILTIN, LOW);
  } else if (buttonPushCounter == 3){
    Serial.println("3rd");
  } else if (buttonPushCounter == 4){
    Serial.println("4th");
  } else if (buttonPushCounter == 5){
  buttonPushCounter -=5;
  }
 }
}