'''
Example usage of the ArdClicker library.
'''
#include <ArdClicker.h>

ArdClicker button(2);

void setup() {
  Serial.begin(9600);
  
  // Initialize the button actions library
  button.begin();

  // Add actions for different button presses
  button.addAction([]() {
    Serial.println("Action for 1st press");
  });
  
  button.addAction([]() {
    Serial.println("Action for 2nd press");
  });
  
  button.addAction([]() {
    Serial.println("Action for 3rd press");
  });
  
  button.addAction([]() {
    Serial.println("Action for 4th press");
  });
}

void loop() {
  button.update(); // Update the button state and trigger actions
}
