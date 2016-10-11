int ledPins[] = {11,10,A5,A4,A3,A2,A1,A0};
int delayvar[] = {1,20,40,80,150,250,1000};
int shiftOutNumbers[] = {320, 377, 292, 304, 281, 274, 258};
int shiftOutVar[] = {128, 384, 896, 1920, 3968, 8064, 16256, 32640};
int shiftOutArrayVar[] = {448, 704, 1216, 2240, 4288, 8384, 16576, 32960};
int factor = 255 / 6;
int selection = 0;
int latchPin = 5; //pin 12 of 595
int dataPin = 3; //pin 14 on the 595
int clockPin = 9; //pin 11 on the 595
int plaatSelectie = 0;
boolean on0 = true;
boolean on1 = true;
boolean safetyOff0 = true;
boolean safetyOff1 = true;

int outputPins[] = {2, 5, 4, 6};
int outputPinSize = sizeof(outputPins) / sizeof(int);
int currentOutputPin = 0;

int inputPins[] = {7, 8};
int inputPinSize = sizeof(inputPins) / sizeof(int);

int buttonsPressed[] = {0, 0, 0, 0, 0, 0, 0, 0};
int buttonSize = sizeof(buttonsPressed) / sizeof(int);

int place;

void setup() {
  for (int i = 0; i < outputPinSize; i++) {
    pinMode(outputPins[i], OUTPUT);
  }
  for (int i = 0; i < inputPinSize; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void displayLEDS() {
  for(int i = 0; i < ledPinsSize; i++) {
    digitalWrite(ledPins[i], HIGH);
    delayMicroseconds(delayvar[ledState[i]]);
    digitalWrite(ledPins[i], LOW);
  }
}

void checkButtonsPressed() {
  for (int i = 0; i < inputPinSize; i++) {
    int buttonState = digitalRead(inputPins[i]);
    place = currentOutputPin*inputPinSize + i;
    if (buttonState == LOW) {
      buttonsPressed[place] = 1;
    } else {
      if buttonsPressed[place] == 1 {
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

void checkButtons() {
  checkButtonsPressed();
  nextOutputPin();
  setOutputPins();
}

void clickButton(int x) {
  tone(6, 150, 100);
  Serial.println(selection);
  switch (x) {
    case 0:     //turn kookplaat on or off
        if (safetyOff0 && plaatSelectie == 0 || safetyOff1 && plaatSelectie == 1){
        Serial.println("on/off");
        if (on0 && plaatSelectie == 0 || on1 && plaatSelectie == 1) {
            if (plaatSelectie == 0){
            on0 = false;
            } else {
            on1 = false;
            }
            resetPinStates();
        } else {
            if (plaatSelectie == 0){
            on0 = true;
            } else {
            on1 = true;
            }
        }
        Serial.println(on0, on1);
        }
    break;
    case 1:     //select right LED
        if (safetyOff0 && plaatSelectie == 0 || safetyOff1 && plaatSelectie == 1){
            Serial.println("select right LED");
            if (selection < (ledPinsSize/2 - 1)+plaatSelectie*4) {
            selection++;
        } else {
            selection = 0+plaatSelectie*4;
        }
        Serial.println(selection);
        }
    break;
    case 2:     //select left LED
        if (safetyOff0 && plaatSelectie == 0 || safetyOff1 && plaatSelectie == 1){
            Serial.println("select left LED");
            if (selection > 0+plaatSelectie*4) {
            selection--;
        } else {
            selection = (ledPinsSize/2-1)+plaatSelectie*4;
        }
        Serial.println(selection);
        }
    break;
    case 3:     //put LED higher
        if (safetyOff0 && plaatSelectie == 0 || safetyOff1 && plaatSelectie == 1){
            Serial.println("put LED higher");
            if ((on0 && plaatSelectie == 0 || on1 && plaatSelectie == 1) && ledState[selection] < 6) {
                ledState[selection]++;
                shiftOutArrayVar[selection] = shiftOutNumbers[ledState[selection]]+shiftOutVar[selection];
            }
            Serial.println(ledState[selection]);
        }
    break;
    case 4:     //put LED lower
        if (safetyOff0 && plaatSelectie == 0 || safetyOff1 && plaatSelectie == 1){
            Serial.println("put LED lower");
            if (ledState[selection] > 0) {
                ledState[selection]--;
                shiftOutArrayVar[selection] = shiftOutNumbers[ledState[selection]]+shiftOutVar[selection];
            }
        Serial.println(ledState[selection]);
        }
    break;
    case 5:     // toggle plaat
        if (safetyOff0 && plaatSelectie == 0 || safetyOff1 && plaatSelectie == 1){
            Serial.println("Toggle plaat selected");
            togglePlaat();
        }
    break;
    case 6:     //toggle safety switch
        Serial.println("Toggle safety switch");
        toggleSafetySwitch();
    break;
  }
}

void resetPinStates() {
  for (int i = 0; i < ledPinsSize/2 + plaatSelectie*4; i++) {
    ledState[i] = 0;
  }
  selection = 0;
  plaatSelectie = 0;
}

void displayNumber(int list[]) {
  int number = 7;
  for (int i = 0; i < 8; i++) {
    digitalWrite(number, list[i]);
    number++;
  }
}

void togglePlaat(){
    if (plaatSelectie == 1){
        plaatSelectie = 0;
        selection -= 4;
    } else {
        plaatSelectie = 1;
        selection += 4;
    }
}

void toggleSafetySwitch(){
    if (plaatSelectie == 0){
        safetyOff0 = !safetyOff0;
    } else {
        safetyOff1 = !safetyOff1;
    }
}

void shiftOutNumber(int number){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, number);
  shiftOut(dataPin, clockPin, MSBFIRST, (number >> 8));
  //Serial.println(data >> 8);
  digitalWrite(latchPin, HIGH);
}

void display(int displaynumber){
   shiftOutNumber(shiftOutNumbers[ledState[displaynumber]]+shiftOutVar[displaynumber]);
}
void loop() {
  checkButtons();
  displayLEDS();
  for(int i = 0; i < ledPinsSize; i++){
    shiftOutNumber(shiftOutArrayVar[i]);
    delay(1);
  }
}
 