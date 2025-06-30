class RotaryEncoder {

  // Class member variables
  private:

    // Pin numbers
    int a;
    int b;
    int d;

    // Encoder states
    bool pastA;
    int position;
    unsigned long pastClickMS;
    const int debounce = 500;

  // Class member functions
  public:

    // Constructor
    // Assign arguments for pin A, B and D to the respective member variables.
    // Set the remaining member variables to thir default values.
    RotaryEncoder(const int& argA, const int& argB, const int& argD) {
      a = argA;
      b = argB;
      d = argD;

      pastA = HIGH;
      position = 90;
      pastClickMS = millis();
    };

    // Set the pin mode for a, b and d to input with pullup resistors.
    // The value will be HIGH when the circuit is open.
    // The value will be LOW when the circuit is closed.
    void bindPins() {
      pinMode(a, INPUT_PULLUP);
      pinMode(b, INPUT_PULLUP);
      pinMode(d, INPUT_PULLUP);
    };

    // Check if there are any turns on the rotary encoder shaft.
    // Returns the updated position, regardless if it changed.
    bool scanRotate() {
      bool presentA = digitalRead(a);

      if (presentA == HIGH && pastA == LOW) {

        if (digitalRead(b) == HIGH) {
          position ++;
        } else {
          position --;
        }

        pastA = presentA;
        return true;

      } else {
        pastA = presentA;
        return false;
      }
    };

    // Check if there are any clicks on the rotary encoder button.
    // Returns true if the button is clicked, otherwise false.
    bool scanClick() {
      if (digitalRead(d) == LOW) {
        if (millis() - pastClickMS > debounce) {
          Serial.println(String(millis()) + " - " + String(pastClickMS) + " = " + String(millis() - pastClickMS) + " > " + String(debounce));

          pastClickMS = millis();
          return true;
        }
      }

      return false;
    };

    int getPosition() {
      return position;
    };

};

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
