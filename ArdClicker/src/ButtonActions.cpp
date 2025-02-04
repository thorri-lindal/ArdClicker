#include "ButtonActions.h"

ButtonActions::ButtonActions(int buttonPin) {
    this->buttonPin = buttonPin;
    buttonState = 0;
    lastButtonState = 0;
    buttonPushCounter = 0;
}

void ButtonActions::begin() {
    pinMode(buttonPin, INPUT);
}

void ButtonActions::update() {
    buttonState = digitalRead(buttonPin);
    
    if (buttonState != lastButtonState) {
        if (buttonState == HIGH) {
            buttonPushCounter++;
            executeAction(buttonPushCounter);
            delay(5); 
        }
        lastButtonState = buttonState;
    }
}

void ButtonActions::addAction(void (*action)()) {
    if (buttonPushCounter < MAX_ACTIONS) {
        actions[buttonPushCounter - 1] = action;
    }
}

void ButtonActions::executeAction(int actionIndex) {
    if (actionIndex > 0 && actionIndex <= MAX_ACTIONS && actions[actionIndex - 1] != nullptr) {
        actions[actionIndex - 1]();
    }
}