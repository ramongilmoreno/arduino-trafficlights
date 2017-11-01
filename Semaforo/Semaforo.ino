// Offset to individual light pin
const int offset_red = 0;
const int offset_yellow = 1;
const int offset_green = 2;

// Traffic light A and B start pin
const int tl_a_base = 0;
const int tl_b_base = 3;

// Input analog speed selector
const int rate = A0;

// Input press button
const int button = A1;

void setup () {
  // Setup input pins
  pinMode(rate, INPUT);
  pinMode(button, INPUT_PULLUP);
  
  // Setup output pins
  for (int i = 0; i < 3; i++) {
    pinMode(tl_a_base + i, OUTPUT);
    digitalWrite(tl_a_base + i, LOW);
    pinMode(tl_b_base + i, OUTPUT);
    digitalWrite(tl_b_base + i, LOW);
  }
}

// State machine
const int state_a_green = 0;
const int state_a_transitioning = 1;
const int state_b_green = 2;
const int state_b_transitioning = 3;
const int states = state_b_transitioning + 1;

// Speed control
const float idleTime = 10;
const float baseTime = 1000;
const float minimumTime = 100;

// Globals

// State
int state = state_a_green;

// Step
int k = 0;

// Speed selection
float speedSelection = 0.5;

// Button requested
boolean buttonRequested = false;

const boolean ON = LOW;
const boolean OFF = HIGH;

void loop () {
  if (buttonRequested) {
    switch (state) {
      case state_a_green:
        state = state_a_transitioning;
        break;
      case state_b_green:
        state = state_b_transitioning;
        break;
    }
  }
  switch (state) {
    case state_a_green:
      digitalWrite(tl_a_base + offset_red, OFF);
      digitalWrite(tl_a_base + offset_yellow, OFF);
      digitalWrite(tl_a_base + offset_green, ON);
      digitalWrite(tl_b_base + offset_red, ON);
      digitalWrite(tl_b_base + offset_yellow, OFF);
      digitalWrite(tl_b_base + offset_green, OFF);
      break;
    case state_a_transitioning:
      digitalWrite(tl_a_base + offset_red, OFF);
      digitalWrite(tl_a_base + offset_yellow, ON);
      digitalWrite(tl_a_base + offset_green, OFF);
      digitalWrite(tl_b_base + offset_red, ON);
      digitalWrite(tl_b_base + offset_yellow, OFF);
      digitalWrite(tl_b_base + offset_green, OFF);
      state = state_b_green;
      break;
    case state_b_green:
      digitalWrite(tl_a_base + offset_red, ON);
      digitalWrite(tl_a_base + offset_yellow, OFF);
      digitalWrite(tl_a_base + offset_green, OFF);
      digitalWrite(tl_b_base + offset_red, OFF);
      digitalWrite(tl_b_base + offset_yellow, OFF);
      digitalWrite(tl_b_base + offset_green, ON);
      break;
    case state_b_transitioning:
      digitalWrite(tl_a_base + offset_red, ON);
      digitalWrite(tl_a_base + offset_yellow, OFF);
      digitalWrite(tl_a_base + offset_green, OFF);
      digitalWrite(tl_b_base + offset_red, OFF);
      digitalWrite(tl_b_base + offset_yellow, ON);
      digitalWrite(tl_b_base + offset_green, OFF);
      state = state_a_green;
      break;
  }
  /*
  // Action
  k = (k + 1) % 6;
  for (int j = 0; j < 6; j++) {
    boolean actualValue = k == j ? LOW : HIGH;
    digitalWrite(0 + j, buttonRequested ? HIGH : actualValue);
  }
  */

  // Button requested reset at each step
  buttonRequested = false;
  
  // Speed control
  speedSelection = analogRead(rate) / 1023.;
  for (int l = 0; l < (((speedSelection * (baseTime - minimumTime)) + minimumTime) / idleTime); l++) {
    // Button is setup with a pullup resistor, so it is pressed in low
    if (!digitalRead(button)) {
      buttonRequested = true;
    }
    delay(idleTime);
  }
}

