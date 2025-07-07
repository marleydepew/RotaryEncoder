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
    uint8_t a_pin;
    uint8_t b_pin;
    uint8_t d_pin;

    // Encoder states
    bool a_val_old;
    unsigned long last_turn_ms;
    unsigned long last_click_ms;

    // Positions
    uint8_t shaft_pos;
    uint8_t shaft_pos_min;
    uint8_t shaft_pos_max;
    
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
    RotaryEncoder(const uint8_t& a_pin_parm, const uint8_t& b_pin_parm, const uint8_t& d_pin_parm, const uint8_t& min_parm, const uint8_t& max_parm);
    RotaryEncoder(const uint8_t& a_pin_parm, const uint8_t& b_pin_parm, const uint8_t& min_parm, const uint8_t& max_parm);

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
    void setPosition(const uint8_t& shaft_pos_new);

    // Set private member data, min limit.
    void setMin(const uint8_t& shaft_pos_min_new);

    // Set private member data, min limit.
    void setMax(const uint8_t& shaft_pos_max_new);


};
#endif