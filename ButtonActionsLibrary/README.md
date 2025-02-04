# ButtonActionsLibrary

## Overview
The ButtonActionsLibrary is an Arduino library designed to simplify the handling of button presses. It allows users to trigger multiple actions with a single button, making it ideal for projects that require versatile input handling.

## Features
- Easy setup and configuration of button actions.
- Support for multiple actions triggered by a single button.
- Simple API for adding and managing actions.

## Installation
1. Download the ButtonActionsLibrary from the repository.
2. Extract the contents to your Arduino libraries folder (usually located in `Documents/Arduino/libraries`).
3. Restart the Arduino IDE to recognize the new library.

## Usage
To use the ButtonActionsLibrary in your project, include the main library header:

```cpp
#include <ButtonActionsLibrary.h>
```

### Example
Here is a simple example of how to use the library:

```cpp
#include <ButtonActionsLibrary.h>

ButtonActions button;

void setup() {
  button.begin(2); // Initialize button on pin 2
  button.addAction([]() { Serial.println("Action 1 triggered!"); });
  button.addAction([]() { Serial.println("Action 2 triggered!"); });
}

void loop() {
  button.update(); // Check button state and trigger actions
}
```

## API Reference

### ButtonActions Class
- **void begin(int pin)**: Initializes the button on the specified pin.
- **void update()**: Reads the button state and triggers the corresponding action.
- **void addAction(void (*action)())**: Adds a new action to be triggered on button press.

## License
This library is released under the MIT License. See the LICENSE file for more details.