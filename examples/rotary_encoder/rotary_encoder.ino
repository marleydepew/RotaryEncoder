#include <rotary_encoder.h>

RotaryEncoder rudder(3, 4, 5);
RotaryEncoder sail(6, 7, 8);

// In Arduino, this runs once to set up the inputs and outputs.
void setup() {
  rudder.bindPins();
  sail.bindPins();

  Serial.begin(9600);
}

// In Arduino, this is the main loop of the program.
// Main
void loop() {
  
  if(rudder.scanRotate()) {
    Serial.println("Rudder: " + 
            String(rudder.getPosition()));
  }

  if(sail.scanRotate()) {
    Serial.println("Sail: " + 
            String(sail.getPosition()));
  }

  if (rudder.scanClick()) {
    Serial.println("Rudder: Click!");
  }

  if (sail.scanClick()) {
    Serial.println("Sail: Click!");
  }

  delay(1);
}
