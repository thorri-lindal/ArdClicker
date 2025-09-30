// ButtonActions.h
// Save this file as: ButtonActions.h

#ifndef BUTTONACTIONS_H
#define BUTTONACTIONS_H

#include <Arduino.h>

#define MAX_ACTIONS 20

// Action types
enum ActionType {
    ON_PRESS,           // Triggered on button press
    ON_RELEASE,         // Triggered on button release
    ON_LONG_PRESS,      // Triggered when held for longPressTime
    ON_DOUBLE_CLICK,    // Triggered on rapid successive presses
    ON_CLICK,           // Triggered on press count (original behavior)
    ON_HOLD,            // Continuously triggered while held
    ON_TOGGLE           // Toggle state on each press
};

class ButtonActions {
public:
    ButtonActions(int buttonPin);
    void begin();
    void update();
    
    // Add action for specific press count (original functionality)
    void addAction(int triggerCount, void (*action)());
    
    // Add action by type
    void addPressAction(void (*action)());
    void addReleaseAction(void (*action)());
    void addLongPressAction(void (*action)(), unsigned long holdTime = 1000);
    void addDoubleClickAction(void (*action)(), unsigned long maxInterval = 300);
    void addHoldAction(void (*action)(), unsigned long interval = 100);
    void addToggleAction(void (*action)());
    
    // Configuration
    void setDebounceDelay(unsigned long ms);
    void setLongPressTime(unsigned long ms);
    void setDoubleClickInterval(unsigned long ms);
    void setHoldInterval(unsigned long ms);
    
    // State queries
    int getPressCount();
    bool isPressed();
    bool isLongPressed();
    unsigned long getPressedDuration();
    bool getToggleState();
    
    // Reset functions
    void resetCounter();
    void resetToggle();

private:
    int buttonPin;
    int buttonState;
    int lastButtonState;
    int buttonPressCount;
    
    // Timing variables
    unsigned long lastDebounceTime;
    unsigned long debounceDelay;
    unsigned long pressStartTime;
    unsigned long lastReleaseTime;
    unsigned long lastPressTime;
    unsigned long longPressTime;
    unsigned long doubleClickInterval;
    unsigned long holdActionInterval;
    unsigned long lastHoldActionTime;
    
    // State flags
    bool longPressFired;
    bool buttonCurrentlyPressed;
    bool toggleState;
    bool waitingForDoubleClick;
    
    struct Action {
        void (*function)();
        ActionType type;
        int triggerCount;      // For ON_CLICK type
        unsigned long timing;  // For timed actions (long press, double-click, hold)
        bool active;
    };
    
    Action actions[MAX_ACTIONS];
    int actionCount;
    
    void executeActions(ActionType type);
    void checkLongPress();
    void checkDoubleClick();
    void checkHold();
};

#endif // BUTTONACTIONS_H
