int ledPins[] = {11,9};
int ledState[] = {3,6};
int factor = 255/6;
int buttonPins[] = {2,4,7,8,12};
int buttonPressed[] = {0,0,0,0,0};
int selection = 0;
boolean on = true;

void setup() {
  for (int i = 0; i < sizeof(ledPins); i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  for (int i = 0; i < sizeof(buttonPins); i++) {
    pinMode(buttonPins[i], INPUT);
  }
}

void displayLEDS() {
  if (on) {
    for (int i = 0; i < sizeof(ledPins); i++) {
      analogWrite(ledPins[i], ledState[i]*factor);
    }
  }
}

void checkButtons() {
  for (int i = 0; i < sizeof(buttonPins); i++) {
    int buttonState = digitalRead(buttonPins[i]);
    if (buttonState == HIGH) {
      buttonPressed[i] = 1;
    } else {
      if (buttonPressed[i] == 1) {
        clickButton(i);
      }
      buttonPressed[i] = 0;
    }
  }
}

void clickButton(int x) {
  switch (x) {
    case 0:     //turn kookplaat on or off
      if (on) {
        on = false;
      } else {
        on = true;
      }
    case 1:     //select right LED
      if (selection < sizeof(ledPins)) {
        selection++;
      } else {
        selection = 0;
      }
    case 2:     //select left LED
      if (selection > 0) {
        selection--;
      } else {
        selection = sizeof(ledPins);
      }
    case 3:     //put LED higher
      if (ledState[selection] < 6) {
        ledState[selection]++;
      }
    case 4:     //put LED lower
      if (ledState[selection] > 0) {
        ledState[selection]--;
      }
  }
}

void loop() {
  checkButtons();
  displayLEDS();
}