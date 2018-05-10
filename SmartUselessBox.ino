#include "state.h"
#include "motor.h"

int state[3];

// Input
#define PIN_LIMIT_SWITCH  4
#define PIN_TOGGLE_SWITCH 5

// Output
#define PIN_MOTOR_1 2
#define PIN_MOTOR_2 3

void setup() {
  Serial.begin(115200);
  // PINS
  // - Input
  pinMode(PIN_LIMIT_SWITCH, INPUT_PULLUP);
  pinMode(PIN_TOGGLE_SWITCH, INPUT_PULLUP);

  // - Output
  pinMode(PIN_MOTOR_1, OUTPUT);
  pinMode(PIN_MOTOR_2, OUTPUT);

  // Initial state
  state[kLIMIT_SWITCH] = NORMAL;
  state[kTOGGLE_SWITCH] = OFF;
  state[kTIME] = millis();

  // Initial motor
  driveMotor(getMotorState(state));
}

void loop() {
  // Update state
  state[kLIMIT_SWITCH] = digitalRead(PIN_LIMIT_SWITCH) == LOW ? PRESSED : NORMAL;
  state[kTOGGLE_SWITCH] = digitalRead(PIN_TOGGLE_SWITCH) == LOW ? ON : OFF;
  state[kTIME] = millis();

  // Update motor
  driveMotor(getMotorState(state));
}

void driveMotor(MOTOR_STATE ms) {
  switch (ms) {
  case REVERSE:
    digitalWrite(PIN_MOTOR_1, HIGH);
    digitalWrite(PIN_MOTOR_2, LOW);
    break;
  case NEUTRAL:
    digitalWrite(PIN_MOTOR_1, HIGH);
    digitalWrite(PIN_MOTOR_2, HIGH);
    break;
  case FORWARD:
    digitalWrite(PIN_MOTOR_1, LOW);
    digitalWrite(PIN_MOTOR_2, HIGH);
    break;
  }
}
