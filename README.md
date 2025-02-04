# ArdClicker ✋🔴

## Overview

ArdClicker is an Arduino library that allows you to handle button presses and execute different actions based on the number of times the button is pressed.

## Features
- Easy setup and configuration of button actions.
- Support for multiple actions triggered by a single button.
- Simple API for adding and managing actions.

## Installation

1. Download the ArdClicker library.
2. Unzip the library and place it in the `libraries` folder of your Arduino sketchbook directory.
3. Restart the Arduino IDE.

## Usage

### Include the Library

Include the ArdClicker library in your sketch:

```cpp
#include <ArdClicker.h>
```

### Example
Here is a simple example of how to use the library:

```cpp
#include <ArdClicker.h>

ArdClicker button(2);

void setup() {
    Serial.begin(9600);
    button.begin();
    button.addAction(action1);
    button.addAction(action2);
    button.addAction(action3);
}

void loop() {
    button.update();
}

void action1() {
    Serial.println("Action 1 executed");
}

void action2() {
    Serial.println("Action 2 executed");
}

void action3() {
    Serial.println("Action 3 executed");
}
```

## API Reference

### ButtonActions Class
- **void begin(int pin)**: Initializes the button on the specified pin.
- **void update()**: Reads the button state and triggers the corresponding action.
- **void addAction(void (*action)())**: Adds a new action to be triggered on button press.

## License
This library is released under the MIT License. See the LICENSE file for more details.
