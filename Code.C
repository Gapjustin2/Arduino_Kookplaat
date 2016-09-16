int ledPins[] = {11, 10};
int ledState[] = {6, 6};
int factor = 255 / 6;
int buttonPins[] = {2, 4, 7, 8, 12};
int buttonPressed[] = {0, 0, 0, 0, 0};
int ledPinsSize = sizeof(ledPins) / sizeof(int);
int buttonPinsSize = sizeof(buttonPins) / sizeof(int);
int selection = 0;
boolean on = true;

int zero[] = {1, 1, 1, 0, 1, 1, 1};
int one[] = {0, 0, 1, 0, 0, 1, 0};
int two[] = {1, 0, 1, 1, 1, 0, 1};
int three[] = {1, 1, 0, 1, 1, 0, 1};
int four[] = {};
int five[] = {};
int six[] = {};

void setup() {
  for (int i = 0; i < ledPinsSize; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  for (int i = 0; i < buttonPinsSize; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
}

void displayLEDS() {
  for (int i = 0; i < ledPinsSize; i++) {
    analogWrite(ledPins[i], ledState[i]*factor);
  }
}

void checkButtons() {
  for (int i = 0; i < buttonPinsSize; i++) {
    int buttonState = digitalRead(buttonPins[i]);
    if (buttonState == LOW) {
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
      Serial.println("on/of");
      if (on) {
        on = false;
        resetPinStates();
      } else {
        on = true;
      }
      Serial.println(on);
      break;
    case 1:     //select right LED
      Serial.println("select right LED");
      if (selection < ledPinsSize - 1) {
        selection++;
      } else {
        selection = 0;
      }
      Serial.println(selection);
      break;
    case 2:     //select left LED
      Serial.println("select left LED");
      if (selection > 0) {
        selection--;
      } else {
        selection = ledPinsSize - 1;
      }
      Serial.println(selection);
      break;
    case 3:     //put LED higher
      Serial.println("put LED higher");
      if (on && ledState[selection] < 6) {
        ledState[selection]++;
      }
      Serial.println(ledState[selection]);
      break;
    case 4:     //put LED lower
      Serial.println("put LED lower");
      if (ledState[selection] > 0) {
        ledState[selection]--;
      }
      Serial.println(ledState[selection]);
      break;
  }
}

void resetPinStates() {
  for (int i = 0; i < ledPinsSize; i++) {
    ledState[i] = 0;
  }
}

void displayNumber(int list[]) {
  int number = 7;
  for (int i = 0; i < 8; i++) {
    digitalWrite(number, list[i]);
    number++;
  }
}

void loop() {
  checkButtons();
  displayLEDS();
}