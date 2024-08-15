// Variables
int blink_dot_length = 220;  // Duration of a dot 
int buttonPin = 2;            
int buttonState = 0;         
int lastButtonState = 1;     
bool isBlinking = false;     
bool restartBlinking = false; 

// Functions
void initializeLED();
void initializeButton();
void checkButtonState();
void displaySequence();
void displayMorse(String symbol);
void restartSequence();

void setup() {
  initializeLED();
  initializeButton();
}

void loop() {
  checkButtonState();
  if (isBlinking) {
    displaySequence();
    delay(1000);  // Wait before restarting
    isBlinking = false;
  }
}

// Function Definitions

void initializeLED() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void initializeButton() {
  pinMode(buttonPin, INPUT);
}

void checkButtonState() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && lastButtonState == HIGH) {
    if (isBlinking) {
      restartBlinking = true;  // Signal to restart blinking
    } else {
      isBlinking = true;  // Start blinking
    }
  }
  lastButtonState = buttonState;
}

void displaySequence() {
  displayMorse("...");   // S
  if (restartBlinking) { restartSequence(); return; }
  displayMorse(".-");    // A
  if (restartBlinking) { restartSequence(); return; }
  displayMorse("--");    // M
  if (restartBlinking) { restartSequence(); return; }
  displayMorse(".-");    // A
  if (restartBlinking) { restartSequence(); return; }
  displayMorse(".-.");   // R
  if (restartBlinking) { restartSequence(); return; }
  displayMorse("-");     // T
  if (restartBlinking) { restartSequence(); return; }
  displayMorse("....");  // H
  if (restartBlinking) { restartSequence(); return; }
}

void displayMorse(String symbol) {
  for (int i = 0; i < symbol.length(); i++) {
    if (restartBlinking) {
      return;  
    }
    if (symbol[i] == '.') {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(blink_dot_length);      // Short Blink For Dot
    } else if (symbol[i] == '-') {   
      digitalWrite(LED_BUILTIN, HIGH);
      delay(blink_dot_length * 3.5); // Long Blink For Line
    }
    digitalWrite(LED_BUILTIN, LOW);
    delay(blink_dot_length);
  }
  // Space between letters
  delay(blink_dot_length * 3);
}

void restartSequence() {
  restartBlinking = false;  // Reset the restart flag
  isBlinking = true;        // Restart blinking
}
