# BlueDroid - Firmware for Modular 3D-Printed Robot

## Overview
This repository contains the firmware for a modular, 3D-printable robot designed for educational and experimental purposes. The robot is controlled via Bluetooth using an ESP32 microcontroller and the BlueDroid Android application. The firmware allows the robot to receive and execute movement commands via the Bluetooth Serial Port Profile (SPP) protocol.

## Features
- **Bluetooth Classic (SPP) communication** for wireless control
- **Modular motor control** with PWM signals
- **Basic movement commands**: forward, backward, turn left, turn right, and stop
- **Status indication using built-in LED**
- **Automatic connection handling**

## Hardware Requirements
- **ESP32-WROOM-32** development board (compatible with ESP32-DevKit)
- **Motor driver** (supports PWM control)
- **DC gear motors** (1:48 or 1:90 ratio, depending on wheel size)
- **18650 battery pack** with **SW6106-based PCB** for power management


## Installation
1. Install **Arduino IDE** (latest version recommended).
2. Add ESP32 support to Arduino IDE via **Board Manager**.
3. Install the **BluetoothSerial** library (included in ESP32 core).
4. Clone or download this repository and open `blueDroidPL.ino` in Arduino IDE.
5. Connect your ESP32 board and select the correct **board type** and **port**.
6. Upload the firmware to your ESP32.

## Bluetooth Communication
- The ESP32 advertises itself as a Bluetooth device with the default name **"BlueDroid"**.
- The firmware waits for a Bluetooth connection and blinks the built-in LED while in pairing mode.
- Once connected, it listens for **text-based commands** terminated by a newline (`\n`).

## Command List
| Command        | Description                    |
|---------------|--------------------------------|
| `Stop`        | Stops all motors              |
| `GoForward`   | Moves the robot forward       |
| `GoBackward`  | Moves the robot backward      |
| `TurnLeft`    | Rotates the robot left        |
| `TurnRight`   | Rotates the robot right       |


## Code Overview
### `setup()`
- Configures GPIO pins as PWM outputs for motor control.
- Initializes the Bluetooth module and starts advertising.
- Blinks the LED until a connection is established.

### `loop()`
- Listens for incoming Bluetooth commands.
- Calls `decodeCommand(command)` to interpret and execute movement instructions.
- Monitors connection status and stops the robot if Bluetooth is disconnected.

### Movement Functions
- `goForward()`, `goBackward()`, `turnLeft()`, `turnRight()`, and `stop()` adjust motor speeds via PWM signals.
- LED indicator provides feedback during movement.

## Controlling the Robot
The robot is designed to be controlled using the **BlueDroid Android application**, which can:
- Connect to the ESP32 via Bluetooth.
- Send movement commands.
- Receive status updates (e.g., battery voltage, battery current).

## License
This project is open-source and released under the **MIT License**.

## Author
Developed by **Andrzej Ptaszyński** as part of an educational robotics project.

## Links
- **3D model files & assembly guide**: [To be added]

