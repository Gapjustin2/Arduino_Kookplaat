int ledPins[] = {11, 10, 4, 8, 7, 6, 1, 2};
int ledState[] = {0, 0, 0, 0, 0, 0, 0, 0};
int shiftOutNumbers[] = {320, 377, 292, 304, 281, 274, 258};
int shiftOutVar[] = {128, 384, 896, 1920, 3968, 8064, 1625616, 32640};
int shiftOutArrayVar[] = {448, 704, 1216, 2240, 4288, 8384,16576, 32960};
int factor = 255 / 6;
int buttonPins[] = {2, 4, 7, 8, 12};
int buttonPressed[] = {0, 0, 0, 0, 0};
int ledPinsSize = sizeof(ledPins) / sizeof(int);
int buttonPinsSize = sizeof(buttonPins) / sizeof(int);
int selection = 0;
int latchPin = 5; //pin 12 of 595
int dataPin = 3; //pin 14 on the 595
int clockPin = 9; //pin 11 on the 595
int plaatSelectie = 0;
boolean on = true;
boolean safetyOff0 = true;
boolean safetyOff1 = true;


void setup() {
  for (int i = 0; i < ledPinsSize; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  for (int i = 0; i < buttonPinsSize; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
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
        if (safetyOff0 && plaatSelectie == 0 || safetyOff1 && plaatSelectie == 0){
        Serial.println("on/of");
        if (on) {
            on = false;
            resetPinStates();
        } else {
            on = true;
        }
        Serial.println(on);
        }
    break;
    case 1:     //select right LED
        if (safetyOff0 && plaatSelectie == 0 || safetyOff1 && plaatSelectie == 0){
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
        if (safetyOff0 && plaatSelectie == 0 || safetyOff1 && plaatSelectie == 0){
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
        if (safetyOff0 && plaatSelectie == 0 || safetyOff1 && plaatSelectie == 0){
            Serial.println("put LED higher");
            if (on && ledState[selection] < 6) {
                ledState[selection]++;
                shiftOutArrayVar[selection] = shiftOutNumbers[ledState[selection]]+shiftOutVar[selection];
            }
            Serial.println(ledState[selection]);
        }
    break;
    case 4:     //put LED lower
        if (safetyOff0 && plaatSelectie == 0 || safetyOff1 && plaatSelectie == 0){
            Serial.println("put LED lower");
            if (ledState[selection] > 0) {
                ledState[selection]--;
                shiftOutArrayVar[selection] = shiftOutNumbers[ledState[selection]]+shiftOutVar[selection];
            }
        Serial.println(ledState[selection]);
        }
    break;
    case 5:     // toggle plaat
        if (safetyOff0 && plaatSelectie == 0 || safetyOff1 && plaatSelectie == 0){
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
  for (int i = 0; i < ledPinsSize; i++) {
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
        selection -= 4
    } else {
        plaatSelectie = 1;
        selection += 4
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
 