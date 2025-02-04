void setup() {
  Serial.begin(9600);
  
  // Initialize the button actions library
  ButtonActions buttonActions;
  buttonActions.begin(2); // Pin 2 for the button

  // Add actions for different button presses
  buttonActions.addAction(1, []() {
    Serial.println("Action for 1st press");
  });
  
  buttonActions.addAction(2, []() {
    Serial.println("Action for 2nd press");
  });
  
  buttonActions.addAction(3, []() {
    Serial.println("Action for 3rd press");
  });
  
  buttonActions.addAction(4, []() {
    Serial.println("Action for 4th press");
  });
}

void loop() {
  buttonActions.update(); // Update the button state and trigger actions
}