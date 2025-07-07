#include "rotary_encoder.h"

// Constructor
// Assign microcontroller analog pin numbers for rotary encoder pins A, B and D.
// Set the remaining member variables to thir default values.
RotaryEncoder::RotaryEncoder(const uint8_t& a_pin_parm, const uint8_t& b_pin_parm, const uint8_t& d_pin_parm, const uint8_t& min_parm, const uint8_t& max_parm) {
  a_pin = a_pin_parm;
  b_pin = b_pin_parm;
  d_pin = d_pin_parm;

  a_val_old = HIGH;
  last_turn_ms = millis();
  last_click_ms = millis();

  shaft_pos_min = min_parm;
  shaft_pos_max = max_parm;
  shaft_pos = (shaft_pos_max + shaft_pos_min) / 2;
};

// Overload the constructor for rotary encoders without push button enabled (without D pin).
RotaryEncoder::RotaryEncoder(const uint8_t& a_pin_parm, const uint8_t& b_pin_parm, const uint8_t& min_parm, const uint8_t& max_parm) {
  this->RotaryEncoder(a_pin_parm, b_pin_parm, 0, min_parm, max_parm);
};

// Set the pin mode for A, B and D to input with pullup resistors.
// The value will be HIGH when the circuit is open.
// The value will be LOW when the circuit is closed.
void RotaryEncoder::bindPins() {
  pinMode(a_pin, INPUT_PULLUP);
  pinMode(b_pin, INPUT_PULLUP);
  
  if (d_pin) {
    pinMode(d_pin, INPUT_PULLUP);
  }
};

// Check if there was any rotation on the rotary encoder shaft.
// Updates shaft_pos and a_val_old with new values.
// Returns TRUE if there was an update, otherwise FALSE.
bool RotaryEncoder::scanRotate() {
  bool a_val_new = digitalRead(a);
  uint8_t delta = 0;

  // We only count a rotation when A moves from LOW to HIGH.
  // See this article to understand the algorithm.
  // https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/#arduino-example-code-1-reading-rotary-encoders
  if (a_val_new == HIGH && a_val_old == LOW) {

    // If B is High, then the shaft is rotating clockwise.
    // If B is LOW, then the shaft is rotating counter-clockwise.
    if (digitalRead(b) == HIGH) {
      delta = 1;
    } else {
      delta = -1;
    }

    // If the shaft is rotated quickly, then it should have bigger steps.
    if (millis() - last_turn_ms < FASTEST_ROTATE_INTERVAL) {
        delta *= FASTEST_ROTATE_STEP;
    } else if (millis() - last_turn_ms < FASTER_ROTATE_INTERVAL) {
        delta *= FASTER_ROTATE_STEP;
    }

    last_turn_ms = millis();
  }

  // Update the position, but keep it between the min and max.
  shaft_pos += delta;
  if (shaft_pos < shaft_pos_min) {
    shaft_pos = shaft_pos_min;
  } else if (shaft_pos > shaft_pos_max) {
    shaft_pos = shaft_pos_max;
  }

  a_old = a_new;
  return delta != 0; 
};

// Check if there are any clicks on the rotary encoder's button.
// Returns TRUE if the button was clicked, otherwise FALSE.
bool RotaryEncoder::scanClick() {
  if (d_pin) {
    if (digitalRead(d_pin) == LOW) {
      if (millis() - last_click_ms > CLICK_DEBOUNCE_INTERVAL) {
        last_click_ms = millis();
        return true;
      }
    }
  }

  return false;
};

// Get private member data, shaft position.
uint8_t RotaryEncoder::getPosition() {
  return shaft_pos;
};

// Set private member data, shaft position.
void RotaryEncoder::setPosition(const uint8_t& shaft_pos_new) {
  shaft_pos = shaft_pos_new;
};

// Set private member data, shaft position minimum.
void RotaryEncoder::setMin(const uint8_t& shaft_pos_min_new) {
  shaft_pos_min = shaft_pos_min_new;
};

// Set private member data, shaft position maximum.
void RotaryEncoder::setMax(const uint8_t& shaft_pos_max_new) {
  shaft_pos_max = shaft_pos_max_new;
};