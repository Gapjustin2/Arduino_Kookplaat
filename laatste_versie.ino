//LED
int ledPins[] = {A0,A1,A2,A3,A4,A5,10,11};
const int ledPinsSize = sizeof(ledPins) / sizeof(int);
int ledState[] = {0, 0, 0, 0, 0, 0, 0, 0};
int delayvar[] = {1,20,40,80,150,250,500};

//Display
int shiftOutNumbers[] = {320, 377, 292, 304, 281, 274, 258};
int shiftOutVar[] = {128, 384, 896, 1920, 3968, 8064, 16256, 32640};
int shiftOutArrayVar[] = {448, 704, 1216, 2240, 4288, 8384, 16576, 32960};

//Buttons
int buttonsPressed[] = {0, 0, 0, 0, 0, 0, 0, 0};
const int buttonSize = sizeof(buttonsPressed) / sizeof(int);
int place;
//Outputpins
int outputPins[] = {2, 4, 7, 8};
const int outputPinSize = sizeof(outputPins) / sizeof(int);
int currentOutputPin = 0;
//Inputpins
int inputPins[] = {13, 12};
const int inputPinSize = sizeof(inputPins) / sizeof(int);

//Shiftregister
const int latchPin = 5; //pin 12 of 595
const int dataPin = 3; //pin 14 on the 595
const int clockPin = 9; //pin 11 on the 595

//Selectie
int plaatSelectie = 0;
int selection = 0;
boolean on0 = true;
boolean on1 = true;
boolean safetyOff0 = true;
boolean safetyOff1 = true;

//Setup
void setup() {
  for (int i = 0; i < outputPinSize; i++) {
    pinMode(outputPins[i], OUTPUT);
  }
  for (int i = 0; i < inputPinSize; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
  }
  for (int i = 0; i < ledPinsSize; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
    tone(6, 311, 1000);  //Star wars theme song
    delay(1000);
    tone(6, 233, 1000);
    delay(1000);
    tone(6, 207, 500);
    delay(500);
    tone(6, 196, 500);
    delay(500);
    tone(6, 175, 500);
    delay(500);
    tone(6, 311, 1000);
    delay(1000);
    tone(6, 233, 2000);
    delay(2000);
}

//Display
void displayLEDS() {
  for(int i = 0; i < ledPinsSize; i++) {
    digitalWrite(ledPins[i], HIGH);
    delayMicroseconds(delayvar[ledState[i]]);
    digitalWrite(ledPins[i], LOW);
  }
}

void displayDisplay() {
  for(int i = 0; i < ledPinsSize; i++){
    shiftOutNumber(shiftOutArrayVar[i]);
    delay(1);
  }
}

void shiftOutNumber(int number){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, number);
  shiftOut(dataPin, clockPin, MSBFIRST, (number >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
}

//Buttons
void checkButtons() {
  checkButtonsPressed();
  nextOutputPin();
  setOutputPins();
}

void checkButtonsPressed() {
  for (int i = 0; i < inputPinSize; i++) {
    int buttonState = digitalRead(inputPins[i]);
    place = currentOutputPin*inputPinSize + i;
    if (buttonState == LOW) {
      buttonsPressed[place] = 1;
    } else {
      if (buttonsPressed[place] == 1) {
        clickButton(place);
      }
      buttonsPressed[place] = 0;
    }
  }
}

void nextOutputPin() {
  currentOutputPin++;
  if (currentOutputPin >= outputPinSize) {
    currentOutputPin = 0;
  }
}

void setOutputPins() {
  for (int i = 0; i < outputPinSize; i++) {
    if (i == currentOutputPin) {
      digitalWrite(outputPins[i], LOW);
    } else {
      digitalWrite(outputPins[i], HIGH);
    }
  }
}

//Actions
void clickButton(int x) {
  tone(6, 150, 100);
  switch (x) {
    case 0:     //turn kookplaat on or off
      changeKookplaatState();
      break;
    case 1:     //select left LED
      selectLED(-1);
      break;
    case 2:     //select right LED
      selectLED(1);
      break;
    case 3:     //put LED higher
      changeLEDamount(1);
      break;
    case 4:     //put LED lower
      changeLEDamount(-1);
      break;
    case 5:     // toggle plaat
      togglePlaat();
      break;
    case 6:     //toggle safety switch
      toggleSafetySwitch();
      break;
  }
}

void selectLED(int a) {
  if (safetyOff0 && plaatSelectie == 0 || safetyOff1 && plaatSelectie == 1) {
    selection += a;
    if (selection < plaatSelectie*4) {
      selection = plaatSelectie*4;
    } else if (selection > 3 + plaatSelectie*4) {
      selection = selection > 3 + plaatSelectie*4;
    }
  }
}

void changeLEDamount(int a) {
  if ((safetyOff0 && plaatSelectie == 0 || safetyOff1 && plaatSelectie == 1) && (on0 && plaatSelectie == 0 || on1 && plaatSelectie == 1)) {
    ledState[selection] += a;
    if (ledState[selection] < 0) {
      ledState[selection] = 0;
    } else if (ledState[selection] > 6) {
      ledState[selection] = 6;
    }
    shiftOutArrayVar[selection] = shiftOutNumbers[ledState[selection]]+shiftOutVar[selection];
  }
}

//Toggle
void changeKookplaatState() {
  Serial.println("on/off");
  if (plaatSelectie == 0 && safetyOff0) {
    on0 = !on0;
    if (!on0) {
      resetPinStates();
    }
  } else if (plaatSelectie == 1 && safetyOff1) {
    on1 = !on1;
    if (!on1) {
      resetPinStates();
    }
  }
}

void togglePlaat() {
  Serial.println("Toggle plaat selected");
  if (plaatSelectie == 0 && safetyOff0) {
    plaatSelectie = 1;
    selection = 4;
  } else if (plaatSelectie == 1 && safetyOff1) {
    plaatSelectie = 0;
    selection = 0;
  }
}

void toggleSafetySwitch() {
  Serial.println("Toggle safety switch");
  if (plaatSelectie == 0) {
    safetyOff0 = !safetyOff0;
  } else {
    safetyOff1 = !safetyOff1;
  }
}

void resetPinStates() {
  for (int i = plaatSelectie*4; i < ledPinsSize/2 + plaatSelectie*4; i++) {
    ledState[i] = 0;
    shiftOutArrayVar[i] = shiftOutNumbers[ledState[i]]+shiftOutVar[i];
  }
}

//Main loop
void loop() {
  checkButtons();
  displayLEDS();
  displayDisplay();
}
 
