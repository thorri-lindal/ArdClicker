# ArdClicker ✋🔴

A comprehensive Arduino library for handling multiple actions from a single button with advanced features.

## ✨ Features

- **🖱️ Multiple Action Types**: Press, Release, Long Press, Double-Click, Hold, Toggle
- **🔢 Click Counting**: Execute different actions based on number of presses
- **⏱️ Long Press Detection**: Trigger actions after holding (customizable duration)
- **⚡ Double-Click Support**: Detect rapid successive button presses
- **🔄 Hold Actions**: Continuously trigger actions while button is held
- **🔀 Toggle State Management**: Track ON/OFF states with each press
- **🛡️ Hardware Debouncing**: Proper debounce implementation for reliable operation
- **⚙️ Fully Configurable**: Customize all timing parameters
- **📊 State Queries**: Check button status, press count, and duration
- **🚀 Non-Blocking**: Works seamlessly without delays
- **🔌 Multiple Buttons**: Support for multiple buttons simultaneously

## 📦 Installation

### Method 1: Arduino Library Manager (Coming Soon)
1. Open Arduino IDE
2. Go to `Sketch → Include Library → Manage Libraries`
3. Search for "ArdClicker"
4. Click Install

### Method 2: Manual Installation
1. Download the ArdClicker library
2. Extract the ZIP file
3. Move the `ArdClicker` folder to your Arduino libraries directory:
   - **Windows**: `Documents\Arduino\libraries\`
   - **Mac**: `~/Documents/Arduino/libraries/`
   - **Linux**: `~/Arduino/libraries/`
4. Restart Arduino IDE

## 🚀 Quick Start

```cpp
#include <ArdClicker.h>

ArdClicker button(2);  // Button on pin 2

void setup() {
    Serial.begin(9600);
    button.begin();
    
    // Add a simple press action
    button.addPressAction(onPress);
}

void loop() {
    button.update();  // Must call every loop!
}

void onPress() {
    Serial.println("Button pressed!");
}
```

## 📚 Usage Examples

### Example 1: LED Toggle
```cpp
#include <ArdClicker.h>

ArdClicker button(2);
const int LED = 13;

void setup() {
    pinMode(LED, OUTPUT);
    button.begin();
    button.addToggleAction(toggleLED);
}

void loop() {
    button.update();
}

void toggleLED() {
    digitalWrite(LED, button.getToggleState());
}
```

### Example 2: Long Press Detection
```cpp
#include <ArdClicker.h>

ArdClicker button(2);

void setup() {
    Serial.begin(9600);
    button.begin();
    
    // Normal press
    button.addPressAction(normalPress);
    
    // Hold for 1 second
    button.addLongPressAction(longPress, 1000);
    
    // Hold for 3 seconds
    button.addLongPressAction(veryLongPress, 3000);
}

void loop() {
    button.update();
}

void normalPress() {
    Serial.println("Quick press!");
}

void longPress() {
    Serial.println("Held for 1 second!");
}

void veryLongPress() {
    Serial.println("Held for 3 seconds!");
}
```

### Example 3: Menu Navigation
```cpp
#include <ArdClicker.h>

ArdClicker button(2);

void setup() {
    Serial.begin(9600);
    button.begin();
    
    // Different actions for different press counts
    button.addAction(1, menu1);
    button.addAction(2, menu2);
    button.addAction(3, menu3);
    button.addAction(5, resetMenu);  // 5 presses = reset
}

void loop() {
    button.update();
}

void menu1() {
    Serial.println("Menu 1 selected");
}

void menu2() {
    Serial.println("Menu 2 selected");
}

void menu3() {
    Serial.println("Menu 3 selected");
}

void resetMenu() {
    Serial.println("Menu reset!");
    button.resetCounter();
}
```

### Example 4: Volume Control
```cpp
#include <ArdClicker.h>

ArdClicker button(2);
int volume = 50;

void setup() {
    Serial.begin(9600);
    button.begin();
    
    // Hold to increase volume continuously
    button.addHoldAction(increaseVolume, 100);
    
    // Double-click to mute
    button.addDoubleClickAction(muteVolume);
}

void loop() {
    button.update();
}

void increaseVolume() {
    if (volume < 100) {
        volume++;
        Serial.print("Volume: ");
        Serial.println(volume);
    }
}

void muteVolume() {
    volume = 0;
    Serial.println("Muted!");
}
```

### Example 5: Multi-Function Device
```cpp
#include <ArdClicker.h>

ArdClicker button(2);

void setup() {
    Serial.begin(9600);
    button.begin();
    
    button.addPressAction(showStatus);           // Every press
    button.addDoubleClickAction(quickStart);     // Double-click
    button.addLongPressAction(enterSetup, 2000); // Hold 2 sec
    button.addToggleAction(powerToggle);         // Toggle state
}

void loop() {
    button.update();
}

void showStatus() {
    Serial.print("Press count: ");
    Serial.println(button.getPressCount());
}

void quickStart() {
    Serial.println("Quick start activated!");
}

void enterSetup() {
    Serial.println("Entering setup mode...");
}

void powerToggle() {
    Serial.print("Power: ");
    Serial.println(button.getToggleState() ? "ON" : "OFF");
}
```

## 🔧 API Reference

### Action Methods

| Method | Description | Example |
|--------|-------------|---------|
| `addPressAction(func)` | Fires on every press | `button.addPressAction(myFunc);` |
| `addReleaseAction(func)` | Fires on button release | `button.addReleaseAction(myFunc);` |
| `addAction(count, func)` | Fires on Nth press | `button.addAction(3, myFunc);` |
| `addLongPressAction(func, ms)` | Fires after holding | `button.addLongPressAction(myFunc, 1000);` |
| `addDoubleClickAction(func, ms)` | Fires on double-click | `button.addDoubleClickAction(myFunc);` |
| `addHoldAction(func, ms)` | Continuously fires while held | `button.addHoldAction(myFunc, 100);` |
| `addToggleAction(func)` | Alternates state each press | `button.addToggleAction(myFunc);` |

### Configuration Methods

| Method | Default | Description |
|--------|---------|-------------|
| `setDebounceDelay(ms)` | 50ms | Button debounce time |
| `setLongPressTime(ms)` | 1000ms | Long press duration threshold |
| `setDoubleClickInterval(ms)` | 300ms | Maximum time between clicks |
| `setHoldInterval(ms)` | 100ms | Hold action repeat rate |

### State Query Methods

| Method | Returns | Description |
|--------|---------|-------------|
| `getPressCount()` | `int` | Total button presses since reset |
| `isPressed()` | `bool` | True if button currently pressed |
| `isLongPressed()` | `bool` | True if long press was triggered |
| `getPressedDuration()` | `unsigned long` | How long button has been held (ms) |
| `getToggleState()` | `bool` | Current toggle state (true/false) |

### Utility Methods

| Method | Description |
|--------|-------------|
| `begin()` | Initialize the button (call in `setup()`) |
| `update()` | Check button state (call in `loop()`) |
| `resetCounter()` | Reset press counter to 0 |
| `resetToggle()` | Reset toggle state to false |

## ⚡ Hardware Setup

### Basic Connection (Pull-down Resistor)
```
Button Pin 1 ──── Arduino Pin 2
Button Pin 2 ──── 5V

Arduino Pin 2 ──── 10kΩ Resistor ──── GND
```

### Alternative (Internal Pull-up)
```
Button Pin 1 ──── Arduino Pin 2
Button Pin 2 ──── GND

In ButtonActions.cpp: pinMode(buttonPin, INPUT_PULLUP);
```

## 🎯 Best Practices

### ✅ DO:
- Call `button.update()` in every loop iteration
- Use non-blocking code in action callbacks
- Test debounce timing with your specific hardware
- Use long press for "dangerous" actions (reset, delete, etc.)
- Combine multiple action types for rich interactions

### ❌ DON'T:
- Use `delay()` in action callbacks (breaks timing)
- Forget to call `button.begin()` in setup
- Register more than 20 actions per button (MAX_ACTIONS limit)
- Use very short debounce delays (< 20ms may be unreliable)

## 🐛 Troubleshooting

**Problem**: Button actions fire multiple times per press  
**Solution**: Increase debounce delay: `button.setDebounceDelay(100);`

**Problem**: Double-click too sensitive or not working  
**Solution**: Adjust interval: `button.setDoubleClickInterval(400);`

**Problem**: Long press fires too quickly  
**Solution**: Increase time: `button.setLongPressTime(1500);`

**Problem**: Hold actions fire too rapidly  
**Solution**: Increase interval: `button.setHoldInterval(200);`

**Problem**: Actions don't fire at all  
**Solution**: Ensure `button.update()` is called in loop and wiring is correct

## 📊 Comparison with Other Libraries

| Feature | ArdClicker | Basic Libraries |
|---------|------------|-----------------|
| Press Detection | ✅ | ✅ |
| Long Press | ✅ | ❌ |
| Double-Click | ✅ | ❌ |
| Hold Actions | ✅ | ❌ |
| Toggle State | ✅ | ❌ |
| Click Counting | ✅ | Limited |
| Proper Debouncing | ✅ | Sometimes |
| Non-Blocking | ✅ | Sometimes |
| Multiple Actions | ✅ (20) | Limited |

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## 📄 License

This library is released under the MIT License. See the LICENSE file for more details.

## 🔗 Links

- [GitHub Repository](#)
- [Issue Tracker](#)
- [Documentation](#)

## 💡 Credits

Created with ❤️ for the Arduino community.

---

**Version**: 2.0  
**Last Updated**: 2025  
**Minimum Arduino IDE**: 1.6.0+
