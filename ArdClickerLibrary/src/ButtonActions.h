// ButtonActions.cpp
// Save this file as: ButtonActions.cpp

#include "ButtonActions.h"

ButtonActions::ButtonActions(int buttonPin) {
    this->buttonPin = buttonPin;
    buttonState = LOW;
    lastButtonState = LOW;
    buttonPressCount = 0;
    
    // Timing defaults
    lastDebounceTime = 0;
    debounceDelay = 50;
    pressStartTime = 0;
    lastReleaseTime = 0;
    lastPressTime = 0;
    longPressTime = 1000;
    doubleClickInterval = 300;
    holdActionInterval = 100;
    lastHoldActionTime = 0;
    
    // State flags
    longPressFired = false;
    buttonCurrentlyPressed = false;
    toggleState = false;
    waitingForDoubleClick = false;
    
    actionCount = 0;
    
    // Initialize actions array
    for (int i = 0; i < MAX_ACTIONS; i++) {
        actions[i].function = nullptr;
        actions[i].type = ON_PRESS;
        actions[i].triggerCount = 0;
        actions[i].timing = 0;
        actions[i].active = false;
    }
}

void ButtonActions::begin() {
    pinMode(buttonPin, INPUT);
}

void ButtonActions::update() {
    int reading = digitalRead(buttonPin);
    
    // Debouncing
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }
    
    if ((millis() - lastDebounceTime) > debounceDelay) {
        // Button state has changed after debounce
        if (reading != buttonState) {
            buttonState = reading;
            
            // BUTTON PRESSED (LOW to HIGH transition)
            if (buttonState == HIGH) {
                buttonCurrentlyPressed = true;
                pressStartTime = millis();
                longPressFired = false;
                buttonPressCount++;
                
                // Execute press actions
                executeActions(ON_PRESS);
                
                // Execute click count actions
                executeActions(ON_CLICK);
                
                // Handle toggle
                toggleState = !toggleState;
                executeActions(ON_TOGGLE);
                
                // Check for double-click
                checkDoubleClick();
                
                lastPressTime = millis();
            }
            // BUTTON RELEASED (HIGH to LOW transition)
            else {
                buttonCurrentlyPressed = false;
                lastReleaseTime = millis();
                
                // Execute release actions (only if not a long press)
                if (!longPressFired) {
                    executeActions(ON_RELEASE);
                }
            }
        }
    }
    
    // Continuous checks while button is pressed
    if (buttonCurrentlyPressed) {
        checkLongPress();
        checkHold();
    }
    
    lastButtonState = reading;
}

void ButtonActions::addAction(int triggerCount, void (*action)()) {
    if (actionCount < MAX_ACTIONS && action != nullptr && triggerCount > 0) {
        actions[actionCount].function = action;
        actions[actionCount].type = ON_CLICK;
        actions[actionCount].triggerCount = triggerCount;
        actions[actionCount].timing = 0;
        actions[actionCount].active = true;
        actionCount++;
    }
}

void ButtonActions::addPressAction(void (*action)()) {
    if (actionCount < MAX_ACTIONS && action != nullptr) {
        actions[actionCount].function = action;
        actions[actionCount].type = ON_PRESS;
        actions[actionCount].timing = 0;
        actions[actionCount].active = true;
        actionCount++;
    }
}

void ButtonActions::addReleaseAction(void (*action)()) {
    if (actionCount < MAX_ACTIONS && action != nullptr) {
        actions[actionCount].function = action;
        actions[actionCount].type = ON_RELEASE;
        actions[actionCount].timing = 0;
        actions[actionCount].active = true;
        actionCount++;
    }
}

void ButtonActions::addLongPressAction(void (*action)(), unsigned long holdTime) {
    if (actionCount < MAX_ACTIONS && action != nullptr) {
        actions[actionCount].function = action;
        actions[actionCount].type = ON_LONG_PRESS;
        actions[actionCount].timing = holdTime;
        actions[actionCount].active = true;
        actionCount++;
    }
}

void ButtonActions::addDoubleClickAction(void (*action)(), unsigned long maxInterval) {
    if (actionCount < MAX_ACTIONS && action != nullptr) {
        actions[actionCount].function = action;
        actions[actionCount].type = ON_DOUBLE_CLICK;
        actions[actionCount].timing = maxInterval;
        actions[actionCount].active = true;
        actionCount++;
    }
}

void ButtonActions::addHoldAction(void (*action)(), unsigned long interval) {
    if (actionCount < MAX_ACTIONS && action != nullptr) {
        actions[actionCount].function = action;
        actions[actionCount].type = ON_HOLD;
        actions[actionCount].timing = interval;
        actions[actionCount].active = true;
        actionCount++;
    }
}

void ButtonActions::addToggleAction(void (*action)()) {
    if (actionCount < MAX_ACTIONS && action != nullptr) {
        actions[actionCount].function = action;
        actions[actionCount].type = ON_TOGGLE;
        actions[actionCount].timing = 0;
        actions[actionCount].active = true;
        actionCount++;
    }
}

void ButtonActions::checkLongPress() {
    if (!longPressFired && (millis() - pressStartTime) >= longPressTime) {
        longPressFired = true;
        executeActions(ON_LONG_PRESS);
    }
}

void ButtonActions::checkDoubleClick() {
    unsigned long timeSinceLastPress = millis() - lastReleaseTime;
    
    if (timeSinceLastPress <= doubleClickInterval && buttonPressCount >= 2) {
        executeActions(ON_DOUBLE_CLICK);
        waitingForDoubleClick = false;
    }
}

void ButtonActions::checkHold() {
    if (millis() - lastHoldActionTime >= holdActionInterval) {
        lastHoldActionTime = millis();
        executeActions(ON_HOLD);
    }
}

void ButtonActions::executeActions(ActionType type) {
    for (int i = 0; i < actionCount; i++) {
        if (actions[i].active && actions[i].type == type) {
            // Special handling for ON_CLICK type (needs count match)
            if (type == ON_CLICK) {
                if (actions[i].triggerCount == buttonPressCount && 
                    actions[i].function != nullptr) {
                    actions[i].function();
                }
            }
            // Special handling for ON_LONG_PRESS (check custom timing)
            else if (type == ON_LONG_PRESS) {
                if (actions[i].timing > 0) {
                    if ((millis() - pressStartTime) >= actions[i].timing) {
                        if (actions[i].function != nullptr) {
                            actions[i].function();
                        }
                    }
                } else {
                    if (actions[i].function != nullptr) {
                        actions[i].function();
                    }
                }
            }
            // All other types
            else {
                if (actions[i].function != nullptr) {
                    actions[i].function();
                }
            }
        }
    }
}

// Configuration methods
void ButtonActions::setDebounceDelay(unsigned long ms) {
    debounceDelay = ms;
}

void ButtonActions::setLongPressTime(unsigned long ms) {
    longPressTime = ms;
}

void ButtonActions::setDoubleClickInterval(unsigned long ms) {
    doubleClickInterval = ms;
}

void ButtonActions::setHoldInterval(unsigned long ms) {
    holdActionInterval = ms;
}

// State query methods
int ButtonActions::getPressCount() {
    return buttonPressCount;
}

bool ButtonActions::isPressed() {
    return buttonCurrentlyPressed;
}

bool ButtonActions::isLongPressed() {
    return longPressFired;
}

unsigned long ButtonActions::getPressedDuration() {
    if (buttonCurrentlyPressed) {
        return millis() - pressStartTime;
    }
    return 0;
}

bool ButtonActions::getToggleState() {
    return toggleState;
}

// Reset methods
void ButtonActions::resetCounter() {
    buttonPressCount = 0;
}

void ButtonActions::resetToggle() {
    toggleState = false;
}
