#include "rotary_encoder.h"

// Constructor
// Assign microcontroller analog pin numbers for rotary encoder pins A, B and D.
// Set the remaining member variables to thir default values.
RotaryEncoder::RotaryEncoder(const uint8_t& pin_a_num, const uint8_t& pin_b_num, const uint8_t& pin_d_num, const uint8_t& min, const uint8_t& max) {
  a = pin_a_num;
  b = pin_b_num;
  d = pin_d_num;

  min_limit = min;
  max_limit = max;
  position = min_limit + ((max_limit - min_limit) / 2);

  a_old = HIGH;
  last_turn_ms = millis();
  last_click_ms = millis();
};

RotaryEncoder::RotaryEncoder(const uint8_t& pin_a_num, const uint8_t& pin_b_num, const uint8_t& min, const uint8_t& max) {
  a = pin_a_num;
  b = pin_b_num;
  d = '\0';

  min_limit = min;
  max_limit = max;
  position = min_limit + ((max_limit - min_limit) / 2);

  a_old = HIGH;
  last_turn_ms = millis();
  last_click_ms = millis();
};

    // Set the pin mode for a, b and d to input with pullup resistors.
    // The value will be HIGH when the circuit is open.
    // The value will be LOW when the circuit is closed.
void RotaryEncoder::bindPins() {
  pinMode(a, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);
  
  if (d != '\0') {
    pinMode(d, INPUT_PULLUP);
  }
};

// Check if there was any rotation on the rotary encoder shaft.
// Returns TRUE if there was an update, otherwise FALSE.
bool RotaryEncoder::scanRotate() {
  bool a_new = digitalRead(a);
  uint8_t delta = 0;

  // We only count a rotation when A moves from LOW to HIGH.
  // See this article to understand the algorithm.
  // https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/#arduino-example-code-1-reading-rotary-encoders
  if (a_new == HIGH && a_old == LOW) {

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
  position += delta;
  if (position < min_limit) {
    position = min_limit;
  } else if (position > max_limit) {
    position = max_limit;
  }

  a_old = a_new;
  return delta != 0; 
};

// Check if there are any clicks on the rotary encoder's button.
// Returns TRUE if the button was clicked, otherwise FALSE.
bool RotaryEncoder::scanClick() {
  if (d != '\0') {
    if (digitalRead(d) == LOW) {
      if (millis() - last_click_ms > CLICK_DEBOUNCE_INTERVAL) {
        last_click_ms = millis();
        return true;
      }
    }
  }

  return false;
};

// Get private member data, position.
uint8_t RotaryEncoder::getPosition() {
  return position;
};

// Set private member data, position.
void RotaryEncoder::setPosition(const uint8_t& new_position) {
  position = new_position;
};

// Set private member data, min limit.
void RotaryEncoder::setMin(const uint8_t& new_min) {
  min_limit = new_min;
};

// Set private member data, min limit.
void RotaryEncoder::setMax(const uint8_t& new_max) {
  max_limit = new_max;
};