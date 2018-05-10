#include "motor.h"
#include "state.h"

const unsigned long delayLength = 1000;
bool delayStarted = false;
unsigned long delayStartTime;
unsigned long diff;

MOTOR_STATE getMotorState(int state[3]) {
  switch (state[kTOGGLE_SWITCH]) {
  case OFF:
    // Trick 1: Waits for one second when after hitting the toggle switch before going back down
    switch (state[kLIMIT_SWITCH]) {
    case NORMAL:
      diff = state[kTIME] - delayStartTime;
      delayStartTime = state[kTIME];

      if (delayStarted && diff >= delayLength) {
        delayStarted = false;
        return REVERSE;
      }

      delayStarted = true;
      return NEUTRAL;
    case PRESSED:
      delayStarted = false;
      return NEUTRAL;
    }
  case ON:
    delayStarted = false;
    // Trick 2: On the way up, stop moving once every 50 milliseconds
    return state[kTIME] % 50 == 0 ? NEUTRAL : FORWARD;
  }
}

