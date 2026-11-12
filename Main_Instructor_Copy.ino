#include <IRremote.hpp>

// Motor pin definitions. A = Right side, B = Left side
#define RIGHT_SPEED_PIN 5   // PWM pin: controls how FAST the right motors spin
#define LEFT_SPEED_PIN  6   // PWM pin: controls how FAST the left motors spin
#define RIGHT_DIR_PIN   7   // HIGH = right motors forward, LOW = backward
#define LEFT_DIR_PIN    8   // HIGH = left motors forward, LOW = backward
#define STANDBY_PIN     3   // HIGH = motors ON, LOW = motors OFF

#define IR_PIN 9            // The IR receiver is plugged into pin 9

// IR remote button codes
#define BTN_UP     0x46
#define BTN_DOWN   0x15
#define BTN_LEFT   0x44
#define BTN_RIGHT  0x43

//Error 1:
// There is no value assigned to MOVE_TIME_MS and speed
const unsigned long MOVE_TIME_MS = 300;       // How long the car keeps moving (in milliseconds) after the last signal from the remote so a quick tap moves the car for about this long.
const int speed = 200;


uint8_t lastButton = 0;             // Remembers the last button we pressed
unsigned long lastSignalTime = 0;   // When we last heard from the remote
bool isMoving = false;              // Is the car moving right now?

// setup() runs once when the car turns on
void setup() {
  Serial.begin(9600);               // Lets us print messages to the serial monitor

  pinMode(RIGHT_SPEED_PIN, OUTPUT);
  pinMode(LEFT_SPEED_PIN, OUTPUT);
  pinMode(RIGHT_DIR_PIN, OUTPUT);
  pinMode(LEFT_DIR_PIN, OUTPUT);
  pinMode(STANDBY_PIN, OUTPUT);

  stopCar();                        // Start with the car not moving

  // Start listening to the remote
  IrReceiver.begin(IR_PIN, DISABLE_LED_FEEDBACK);
  Serial.println("Ready! Press a button on the remote.");
}

void loop() {

  // Did the remote send us something?
  if (IrReceiver.decode()) {
    uint8_t button = IrReceiver.decodedIRData.command;                          // Stores the button pressed in "button" variable
    bool buttonHeld = IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT;    // Is the button held down?
    bool isGoodSignal = IrReceiver.decodedIRData.protocol != UNKNOWN;           // Not noise?
    IrReceiver.resume();            // Get ready for the next signal

    if (isGoodSignal) {
      // If the button is being HELD, the remote sends "repeat" signals.
      // So we just use the last button we saw.
      if (buttonHeld) {
        button = lastButton;
      } else {
        lastButton = button;
        Serial.print("Button code: 0x");    // Prints the code so we can see it
        Serial.println(button, HEX);
      }

      lastSignalTime = millis();            // Remember WHEN we heard it
      buttonLogic(button);                  // Do what that button says
    }
  }

  // If we haven't heard from the remote for MOVE_TIME_MS
  // (button tapped or let go), stop the car.
  if (isMoving && (millis() - lastSignalTime > MOVE_TIME_MS)) {
    stopCar();
  }
}


// Error 2:
// This function decides what the car does for each button
// Use the function list on your reference sheet to solve this
void buttonLogic(uint8_t button) {
  switch (button) {
    case  BTN_UP:    driveForward();  
          isMoving = true;
          break;
    case  BTN_DOWN:  driveBackward();
          isMoving = true;
          break;
    case  BTN_LEFT:  turnLeft();
          isMoving = true;
          break;
    case  BTN_RIGHT: turnRight();
          isMoving = true;
          break;
  }
}

void driveForward() {
  digitalWrite(STANDBY_PIN, HIGH);      // Turn motors ON
  digitalWrite(RIGHT_DIR_PIN, HIGH);    // Right side forward
  digitalWrite(LEFT_DIR_PIN, HIGH);     // Left side forward
  analogWrite(RIGHT_SPEED_PIN, speed);  // Set right speed
  analogWrite(LEFT_SPEED_PIN, speed);   // Set left speed
}

void driveBackward() {
  digitalWrite(STANDBY_PIN, HIGH);
  digitalWrite(RIGHT_DIR_PIN, LOW);     // Right side backward
  digitalWrite(LEFT_DIR_PIN, LOW);      // Left side backward
  analogWrite(RIGHT_SPEED_PIN, speed);
  analogWrite(LEFT_SPEED_PIN, speed);
}

// To turn right, the car spins: left side forward, right side backward
void turnRight() {
  digitalWrite(STANDBY_PIN, HIGH);
  digitalWrite(RIGHT_DIR_PIN, LOW);     // Right side backward
  digitalWrite(LEFT_DIR_PIN, HIGH);     // Left side forward
  analogWrite(RIGHT_SPEED_PIN, speed);
  analogWrite(LEFT_SPEED_PIN, speed);
}

// To turn left, the car spins: right side forward, left side backward
void turnLeft() {
  digitalWrite(STANDBY_PIN, HIGH);
  digitalWrite(RIGHT_DIR_PIN, HIGH);    // Right side forward
  digitalWrite(LEFT_DIR_PIN, LOW);      // Left side backward
  analogWrite(RIGHT_SPEED_PIN, speed);
  analogWrite(LEFT_SPEED_PIN, speed);
}

void stopCar() {
  digitalWrite(STANDBY_PIN, LOW);       // Turn motors OFF
  analogWrite(RIGHT_SPEED_PIN, 0);
  analogWrite(LEFT_SPEED_PIN, 0);
  isMoving = false;
}