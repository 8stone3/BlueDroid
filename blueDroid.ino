#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to enable it.
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

// Pin definitions
#define LED_BUILTIN 2 // Built-in LED indicator
#define BLUETOOTH_NAME "BlueDroid" // Bluetooth device name visible to the phone
#define PWM_FREQUENCY 1000 // PWM frequency setting
#define PWM_RESOLUTION 8 // PWM resolution, 8 bits (values from 0-255)
#define ENG_LEFT_F_PIN 12 // Pin for left motor forward PWM signal
#define ENG_LEFT_B_PIN 14 // Pin for left motor backward control PWM signal
#define ENG_RIGHT_F_PIN 26 // Pin for right motor forward control PWM signal
#define ENG_RIGHT_B_PIN 27 // Pin for right motor backward control PWM signal
#define SPEED_DEFAULT 255 // Default speed

// Command definitions
#define EOL_CHAR '\n' // End-of-line character
#define COMMAND_STOP "Stop" // Stop command
#define COMMAND_FORWARD "GoForward" // Forward command
#define COMMAND_BACKWARD "GoBackward" // Backward command
#define COMMAND_LEFT "TurnLeft" // Turn left command
#define COMMAND_RIGHT "TurnRight" // Turn right command
#define COMMAND_SET_SPEED "SetSpeed" // Set speed command

BluetoothSerial SerialBT;
int speed = SPEED_DEFAULT;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Set LED pin as output
  digitalWrite(LED_BUILTIN, LOW); // Ensure LED is off initially

  // Configure PWM for motor control
  ledcAttach(ENG_LEFT_F_PIN, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcAttach(ENG_LEFT_B_PIN, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcAttach(ENG_RIGHT_F_PIN, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcAttach(ENG_RIGHT_B_PIN, PWM_FREQUENCY, PWM_RESOLUTION);
  
  stop(); // Stop all motors initially
  Serial.begin(115200); // Start serial monitor for debugging
  SerialBT.begin(BLUETOOTH_NAME); // Start Bluetooth communication
  
  Serial.println("Waiting for Bluetooth connection...");
  while (!SerialBT.connected()) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
  Serial.println("Bluetooth connected!");
}

void loop() {
  // Wait for a new command
  if (SerialBT.available() > 1) {
    String command = SerialBT.readStringUntil(EOL_CHAR);
    Serial.print("Received command: ");
    Serial.println(command);
    decodeCommand(command);
  }
  
  // Check if Bluetooth connection is lost
  if (!SerialBT.connected()) {
    Serial.println("Bluetooth disconnected! Stopping robot.");
    stop();
    while (!SerialBT.connected()) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
    }
    Serial.println("Bluetooth reconnected!");
  }
}

// Execute a function based on the received command
void decodeCommand(String command) {
  if (command == COMMAND_STOP) {
    stop();
  } else if (command == COMMAND_FORWARD) {
    goForward();
  } else if (command == COMMAND_BACKWARD) {
    goBackward();
  } else if (command == COMMAND_LEFT) {
    turnLeft();
  } else if (command == COMMAND_RIGHT) {
    turnRight();
  }
}

void turnRight() {
  ledcWrite(ENG_LEFT_F_PIN, speed);
  ledcWrite(ENG_LEFT_B_PIN, 0);
  ledcWrite(ENG_RIGHT_F_PIN, 0);
  ledcWrite(ENG_RIGHT_B_PIN, speed);
  digitalWrite(LED_BUILTIN, HIGH);
}

void turnLeft() {
  ledcWrite(ENG_LEFT_F_PIN, 0);
  ledcWrite(ENG_LEFT_B_PIN, speed);
  ledcWrite(ENG_RIGHT_F_PIN, speed);
  ledcWrite(ENG_RIGHT_B_PIN, 0);
  digitalWrite(LED_BUILTIN, HIGH);
}

void goBackward() {
  ledcWrite(ENG_LEFT_F_PIN, 0);
  ledcWrite(ENG_LEFT_B_PIN, speed);
  ledcWrite(ENG_RIGHT_F_PIN, 0);
  ledcWrite(ENG_RIGHT_B_PIN, speed);
  digitalWrite(LED_BUILTIN, HIGH);
}

void goForward() {
  ledcWrite(ENG_LEFT_F_PIN, speed);
  ledcWrite(ENG_LEFT_B_PIN, 0);
  ledcWrite(ENG_RIGHT_F_PIN, speed);
  ledcWrite(ENG_RIGHT_B_PIN, 0);
  digitalWrite(LED_BUILTIN, HIGH);
}

void stop() {
  ledcWrite(ENG_LEFT_F_PIN, 0);
  ledcWrite(ENG_LEFT_B_PIN, 0);
  ledcWrite(ENG_RIGHT_F_PIN, 0);
  ledcWrite(ENG_RIGHT_B_PIN, 0);
  digitalWrite(LED_BUILTIN, LOW);
}
