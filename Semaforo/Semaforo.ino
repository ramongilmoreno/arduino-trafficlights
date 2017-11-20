// Offset to individual light pin
const int offset_red = 0;
const int offset_yellow = 1;
const int offset_green = 2;

// Traffic light A and B start pin
const int tl_a_base = 0;
const int tl_b_base = 3;

// Auto mode by default with pull up
const int mode = A0;

// Input press button
const int button = A1;

// Input analog speed selector
const int rate = A2;

// Input analog speed selector
const int greenDuration = A3;


void setup () {
  // Setup input pins
  pinMode(mode, INPUT_PULLUP);
  pinMode(button, INPUT_PULLUP);
  pinMode(rate, INPUT);
  pinMode(greenDuration, INPUT);
  
  // Setup output pins
  for (int i = 0; i < 3; i++) {
    pinMode(tl_a_base + i, OUTPUT);
    digitalWrite(tl_a_base + i, HIGH);
    pinMode(tl_b_base + i, OUTPUT);
    digitalWrite(tl_b_base + i, HIGH);
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
const float baseTime = 5000;
const float minimumTime = 100;
const int greenIterations = 50;
const int greenIterationsMinimum = 0;

// Globals

// State
int state = state_a_green;
int stateGreenIterations = -1;

// Speed selection
float speedSelection = 0.5;

// Button requested
boolean buttonRequested = false;

const boolean ON = LOW;
const boolean OFF = HIGH;

boolean isAuto () {
  return digitalRead(mode) != LOW;
}

boolean timeForAChange () {
  if (isAuto()) {
    // Check if it is time for a transition
    int calculatedIterations =
        ((analogRead(greenDuration) / 1023.) * (greenIterations - greenIterationsMinimum)) +
        greenIterationsMinimum; 
    return stateGreenIterations >= calculatedIterations;
  } else {
    return false;
  }
}

void loop () {
  if (buttonRequested) {
    // Obey to button immediately
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
      stateGreenIterations++;
      if (timeForAChange()) {
        state = state_a_transitioning;
        stateGreenIterations = -1;
      }
      break;
    case state_a_transitioning:
      digitalWrite(tl_a_base + offset_red, OFF);
      digitalWrite(tl_a_base + offset_yellow, ON);
      digitalWrite(tl_a_base + offset_green, OFF);
      digitalWrite(tl_b_base + offset_red, ON);
      digitalWrite(tl_b_base + offset_yellow, OFF);
      digitalWrite(tl_b_base + offset_green, OFF);
      state = state_b_green;
      stateGreenIterations = -1;
      break;
    case state_b_green:
      digitalWrite(tl_a_base + offset_red, ON);
      digitalWrite(tl_a_base + offset_yellow, OFF);
      digitalWrite(tl_a_base + offset_green, OFF);
      digitalWrite(tl_b_base + offset_red, OFF);
      digitalWrite(tl_b_base + offset_yellow, OFF);
      digitalWrite(tl_b_base + offset_green, ON);
      stateGreenIterations++;
      if (timeForAChange()) {
        state = state_b_transitioning;
        stateGreenIterations = -1;
      }
      break;
    case state_b_transitioning:
      digitalWrite(tl_a_base + offset_red, ON);
      digitalWrite(tl_a_base + offset_yellow, OFF);
      digitalWrite(tl_a_base + offset_green, OFF);
      digitalWrite(tl_b_base + offset_red, OFF);
      digitalWrite(tl_b_base + offset_yellow, ON);
      digitalWrite(tl_b_base + offset_green, OFF);
      state = state_a_green;
      stateGreenIterations = -1;
      break;
  }

  // Speed control with button check (to detect button pushes as short as idleTime)
  // If button was requested in previous step do not check again or
  // transition defined in this loop will not be show on the output
  boolean wasButtonRequested = buttonRequested;
  buttonRequested = false;
  for (int l = 0; l < ((((analogRead(rate) / 1023.) * (baseTime - minimumTime)) + minimumTime) / idleTime); l++) {
    if (!wasButtonRequested) {
      // Button is setup with a pullup resistor, so it is pressed in low
      if (!digitalRead(button)) {
        buttonRequested = true;
      }
    }
    delay(idleTime);
  }
}

