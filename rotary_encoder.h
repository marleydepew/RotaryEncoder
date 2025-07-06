#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <Arduino.h>

// See this article to understand how rotary encoders work and the algorithm to read them.
// http://lastminuteengineers.com/rotary-encoder-arduino-tutorial/#how-rotary-encoders-work
// 
//     D E   The D pin is for the push button, E is it's ground.
//     | |
//   -------
//   |     |  Bottom view of the rotary encoder.
//   -------
//    | | |
//    A C B   A and B pins measure the shaft rotation, C is their ground.
// 
class RotaryEncoder {

  // Class member variables
  private:

    // Pin numbers
    uint8_t a;
    uint8_t b;
    uint8_t d;

    // Encoder states
    bool a_old;
    uint8_t position;
    unsigned long last_turn_ms;
    unsigned long last_click_ms;

    // Limits
    uint8_t min_limit;
    uint8_t max_limit;
    
    // CONSTANTS
    static const int CLICK_DEBOUNCE_INTERVAL = 500;
    static const int FASTER_ROTATE_INTERVAL = 250;
    static const int FASTER_ROTATE_STEP = 9;
    static const int FASTEST_ROTATE_INTERVAL = 100;
    static const int FASTEST_ROTATE_STEP = 18;

  // Class member functions
  public:

    // Constructor
    // Assign microcontroller analog pin numbers for rotary encoder pins A, B and D.
    // Set the remaining member variables to thir default values.
    RotaryEncoder(const uint8_t& pin_a_num, const uint8_t& pin_b_num, const uint8_t& pin_d_num, const uint8_t& minimum, const uint8_t& maximum);
    RotaryEncoder(const uint8_t& pin_a_num, const uint8_t& pin_b_num, const uint8_t& minimum, const uint8_t& maximum);

    // Set the pin mode for a, b and d to input with pullup resistors.
    // The value will be HIGH when the circuit is open.
    // The value will be LOW when the circuit is closed.
    void bindPins();

    // Check if there was any rotation on the rotary encoder shaft.
    // Returns TRUE if there was an update, otherwise FALSE.
    bool scanRotate();

    // Check if there are any clicks on the rotary encoder's button.
    // Returns TRUE if the button was clicked, otherwise FALSE.
    bool scanClick();

    // Get private member data, position.
    int getPosition();

    // Set private member data, position.
    void setPosition(const uint8_t& new_position);

    // Set private member data, min limit.
    void setMin(const uint8_t& new_min);

    // Set private member data, min limit.
    void setMax(const uint8_t& new_max);


};
#endif