#include <ButtonActionsLibrary.h>

ButtonActions button(2);  // Button on pin 2

void setup() {
    Serial.begin(9600);
    button.begin();
    
    // Add different actions
    button.addPressAction(onPress);
    button.addLongPressAction(onLongPress, 1000);
    button.addDoubleClickAction(onDoubleClick);
    button.addToggleAction(onToggle);
    
    Serial.println("Button demo ready!");
}

void loop() {
    button.update();  // MUST call this every loop!
}

void onPress() {
    Serial.println("Button pressed!");
}

void onLongPress() {
    Serial.println("Long press detected!");
}

void onDoubleClick() {
    Serial.println("Double-click!");
}

void onToggle() {
    Serial.print("Toggle: ");
    Serial.println(button.getToggleState() ? "ON" : "OFF");
}
